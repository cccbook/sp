var c = require("./ccc");

var symTable = {};

var tempIdx = 0;
var nextTemp=function() { return "T"+tempIdx++; }

var stack = [];
var push=function(o) { stack.push(o); }
var pop=function() { return stack.pop(); }

var tokens = [];
var tokenIdx = 0;
// 本來應該用 .*? 來比對 /*...*/ 註解的，但 javascript 的 . 並不包含 \n, 因此用 \s\S 代替 . 就可以了。
var retok = /(\/\*[\s\S]*?\*\/)|(\/\/[^\r\n])|(\d+)|([a-zA-Z]\w*)|(\r?\n)|(.)/gm; // *?, +? non greedy, m for multiline

var source  = "";
var scan=function(text) { 
  tokenIdx = 0;
  tokens = text.match(retok); 
  return tokens; 
}

var error=function(o) {  c.printf("Error: %j\n", o); }
var pcode = function(op, t, t1, t2) { c.printf("%s %s %s %s\n", op, t, t1, t2); }

var next=function(o) {
  if (isNext(o))
    return tokens[tokenIdx++];
  error(token);
}

var isNext=function(o) {
  if (tokenIdx >= tokens.length) 
    return false;
  var token = tokens[tokenIdx];
  if (o instanceof RegExp) {
    return token.match(o);
  } else {
    return (token == o);
  }
}

var compile=function(text) {
  scan(text);
  c.printf("text=%s\n", text);
  c.printf("tokens=%j\n", tokens);
  E();
  c.printf("symTable=%j\n", symTable);
}

var E=function() { // E=T ([+-] T)*
  push('E');
  t1 = T();
  while (isNext(/[\+\-]/)) {
    op = next(/[\+\-]/);
    t = nextTemp();
    t2 = T();
    pcode(op, t, t1, t2);
    t1 = t;
  }
  pop('E');
  return t1;
}

var T=function() { // T=F ([*/] F)*
  push('T');
  f1 = F();
  while (isNext(/[\*\/]/)) {
    op = next(/[*\/]/);
    f2 = F();
    f = nextTemp();
    pcode(op, f, f1, f2);
    f1 = f;
  }
  pop('T');
  return f1;
}

var reNumber = /\d+/;
var reId = /[a-zA-Z]\w*/;

var F=function() {  // F=NUMBER | ID | ( E )
  push('F');
  if (isNext("(")) {
    next("(");
    f = E();
    next(")");
  } else if (isNext(reNumber)) {
    number = next(reNumber);
    f = nextTemp();
    pcode("=", f, number, "");
  } else if (isNext(reId)) {
    f = id = next(reId);
    symTable[id] = "ID";
  }
  pop('F');
  return f;
}

c.printf("=== EBNF Grammar =====\n");
c.printf("E=T ([+-] T)*\n");
c.printf("T=F ([*/] F)*\n");
c.printf("F=NUMBER | ID | '(' E ')'\n");
compile("32+5*(182+degree*4-20)");
// printf("typeof(/\w+/)=%s /\w+/ instanceof RegExp=%s\n", typeof(/\w+/), /\w+/ instanceof RegExp);
// printf("typeof(str)=%s\n", typeof("str"));
