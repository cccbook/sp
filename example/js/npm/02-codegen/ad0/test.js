var assert = require('assert'),
		diff = require('./ad0').diff;

function test(fn, at, derivative) {
	assert.equal(diff(fn, at), derivative.call(null, at));
}

function err(fn, at, derivative) {
	return Math.abs(diff(fn, at) - derivative.call(null, at));
}

function xsquared(x) {
	return x * x;
}

function xcubed(x) {
	return x * x * x;
}

function e_xsquared(x) {
	return Math.exp(x * x);
}

function e_sin_x2(x) {
	return Math.exp(Math.sin(x * x));
}

function x_over_ln_x(x) {
	return x / Math.log(x);
}

function polynomial(x) {
	return x*x*x*x + (2*x+2) * (2*x+2);
}

function test_assignment(x) {
	var result = 1;
	result *= x*x+x;
	result += x;
	result -= 1;
	return result;
}

//approximation of the gamma function
function gamma(x) {
	var w = 1/x;
	return Math.exp((x - 0.5)*Math.log(x) - x) * Math.sqrt(2*Math.PI) * (1+w*(1/12 + w*(1/288 - w*(139/51840 - w*(571/2488320)))));
}


function fact(n) {
	if (n === 0 || n === 1) return 1;
	return n * fact(n-1);
}


test(xsquared, 3, function(x) { return 2*x; });
test(xcubed, 4, function(x) { return 3*x*x; });
test(e_xsquared, 2, function(x) { return 2*x*Math.exp(x*x); });
test(e_sin_x2, Math.PI/2, function(x) { return 2*x*Math.exp(Math.sin(x*x))*Math.cos(x*x); });
test(x_over_ln_x, 5, function(x) { return (Math.log(x) - 1) / (Math.log(x) * Math.log(x)); });
test(polynomial, 7, function(x) { return 4*x*x*x + 8*x + 8; });
test(test_assignment, 10, function(x) { return 2 * x + 2;});
test(gamma, 5.3, function() { return 59.798083889488986 }); //verified with wolfram alpha

//Note: only for positive integer x
assert.ok(0.00001 > err(gamma, 4, function(x) {
	var c = 0.5772156649015329; //Euler–Mascheroni constant
	var m = x-1, sum = 0;
	for (var k = 1; k <= m; k++) {
		sum += 1/k;
	}
	return fact(m) * (-c + sum);
}));

/*
// add by ccc
function mul(p) {
  let x = p.x, y = p.y
	return x * y;
}

test(mul, {x:3,y:2}, function(p) { return 2*p.y; });
*/