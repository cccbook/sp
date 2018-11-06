var uglify = require("uglify-js"),
		jsp = uglify.parser,
		pro = uglify.uglify,
		vm = require('vm');

function Dual(a, b) {
	return {a: a, b: b || 0};
}

var AD = {
	neg: function(x) {
		return Dual(-x.a, -x.b);
	},
	incr: function(x) {
		++x.a;
	},
	decr: function(x) {
		--x.a;
	},
	gt: function(x0, x1) {
		return x0.a > x1.a;
	},
	gte: function(x0, x1) {
		return x0.a >= x1.a;
	},
	lt: function(x0, x1) {
		return x0.a < x1.a;
	},
	lte: function(x0, x1) {
		return x0.a <= x1.a;
	},
	eq: function(x0, x1) {
		return x0.a == x1.a;
	},
	add: function(x0, x1) {
		return Dual(x0.a + x1.a, x0.b + x1.b);
	},
	sub: function(x0, x1) {
		return Dual(x0.a - x1.a, x0.b - x1.b);
	},
	mul: function(x0, x1) {
		return Dual(x0.a * x1.a, x0.a * x1.b + x1.a * x0.b);
	},
	div: function(x0, x1) {
		return Dual(x0.a / x1.a, (x1.a * x0.b - x0.a * x1.b) / (x1.a * x1.a));
	},
	addAssign: function(x0, x1) {
		var sum = AD.add(x0, x1);
		x0.a = sum.a;
		x0.b = sum.b;
	},
	subAssign: function(x0, x1) {
		var diff = AD.sub(x0, x1);
		x0.a = diff.a;
		x0.b = diff.b;
	},
	mulAssign: function(x0, x1) {
		var prod = AD.mul(x0, x1);
		x0.a = prod.a;
		x0.b = prod.b;
	},
	divAssign: function(x0, x1) {
		var quot = AD.div(x0, x1);
		x0.a = quot.a;
		x0.b = quot.b;
	},
	sqrt: function(x) {
		return Dual(Math.sqrt(x.a), x.b * 0.5 / Math.sqrt(x.a));
	},
	sin: function(x) {
		return Dual(Math.sin(x.a), x.b * Math.cos(x.a));
	},
	cos: function(x) {
		return Dual(Math.cos(x.a), -x.b * Math.sin(x.a));
	},
	tan: function(x) {
		return Dual(Math.tan(x.a), x.b / (Math.cos(x.a) * Math.cos(x.a)));
	},
	asin: function(x) {
		return Dual(Math.asin(x.a), x.b / Math.sqrt(1 - x.a * x.a));
	},
	acos: function(x) {
		return Dual(Math.acos(x.a), -x.b / Math.sqrt(1 - x.a * x.a));
	},
	atan: function(x) {
		return Dual(Math.atan(x.a), x.b / (1 + x.a * x.a));
	},
	log: function(x) {
		return Dual(Math.log(x.a), x.b / x.a);
	},
	exp: function(x) {
		return Dual(Math.exp(x.a), x.b * Math.exp(x.a));
	},
	abs: function(x) {
		var b;
		if (x.a > 0) {
			b = 1;
		} else if (x.a < 0) {
			b = -1;
		} else {
			b = NaN;
		}
		return Dual(Math.abs(x.a), x.b * b);
	},
	PI: Dual(Math.PI),
	E: Dual(Math.E),
	LOG2E: Dual(Math.LOG2E),
	LN2: Dual(Math.LN2),
	LN10: Dual(Math.LN10),
	LOG10E: Dual(Math.LOG10E),
	SQRT2: Dual(Math.SQRT2),
	SQRT1_2: Dual(Math.SQRT1_2)
}


function transform(ast) {
	var w = pro.ast_walker(), walk = w.walk, scope;
	var binOpMap = {
		'+': 'add',
		'-': 'sub',
		'*': 'mul',
		'/': 'div',
		'<': 'lt',
		'<=': 'lte',
		'>': 'gt',
		'>=': 'gte',
		'==': 'eq',
		'===': 'eq'
	};
	var unOpMap = {
		'-': 'neg',
		'--': 'decr',
		'++': 'incr'
	};
	var assignOpMap = {
		'+': 'addAssign',
		'-': 'subAssign',
		'*': 'mulAssign',
		'/': 'divAssign'
	};
	return w.with_walkers({
		'num': function(num) {
			return ['call', ['name', 'Dual'], [['num', num]]];
		},
		'unary-prefix': function(op, expr) {
			if (unOpMap[op]) {
				return ['call', ['dot', ['name', 'AD'], unOpMap[op]], [walk(expr)]];
			}
      return [this[0], op, walk(expr)];
		},
		'unary-postfix': function(op, expr) {
			if (unOpMap[op]) {
				return ['call', ['dot', ['name', 'AD'], unOpMap[op]], [walk(expr)]];
			}
      return [this[0], op, walk(expr)];
		},
		'binary': function(op, left, right) {
			if (binOpMap[op]) {
				return ['call', ['dot', ['name', 'AD'], binOpMap[op]], [walk(left), walk(right)]];
			}
	    return [ this[0], op, walk(left), walk(right) ];
		},
    'assign': function(op, lvalue, rvalue) {
			if (assignOpMap[op]) {
				return ['call', ['dot', ['name', 'AD'], assignOpMap[op]], [walk(lvalue), walk(rvalue)]];
			}
			return [ this[0], op, walk(lvalue), walk(rvalue) ];
    },
		'name': function(name) {
			if (name === 'Math') {
				return [this[0], 'AD'];
			}
		  return [this[0], name];
		},
	}, function() {
		return walk(pro.ast_add_scope(ast));
	});
}

function diff(f, at) {
	var ast = jsp.parse('(' + f.toString() + ')');
	var transformed = transform(ast);
	var generated = pro.gen_code(transformed);
	var context = vm.createContext({
		AD: AD,
		at: Dual(at, 1),
		Dual: Dual,
		console: console,
	});
	vm.runInContext('result = ('+generated+')(at)', context);
	return context.result.b;
}

exports.diff = diff;
