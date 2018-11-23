/* EBNF 語法
E=T ([+ -] T)*
T=F ([* /] F)*
F=NUMBER | ID | ( E )
*/

var tokens = [];
var tokenIdx = 0;
// 本來應該用 .*? 來比對 /*...*/ 註解的，但 javascript 的 . 並不包含 \n, 因此用 \s\S 代替 . 就可以了。
var retok = /(\/\*[\s\S]*?\*\/)|(\/\/.*\r?\n)|(\d+)|([a-zA-Z]\w*)|(\r?\n)|(.)/gm; // *?, +? non greedy, m for multiline
var source  = ''

var scan=function(text) { 
  tokenIdx = 0;
  tokens = text.match(retok); 
  return tokens; 
}

var error=function(o) {
  console.log('Error: %j', o)
  process.exit(1)
}

var next=function(o) {
  if (isNext(o)) {
    let token = tokens[tokenIdx++]
    console.log(indent() + token)
    return token
  }
  error(tokens);
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

var stack = [];
var indent=function() { return ''.padStart(stack.length*2) }
var push=function(o) {
  console.log(indent() + '+' + o)
  stack.push(o)
}

var pop=function() {
  let o = stack.pop()
  console.log(indent() + '-' + o)
  return o
}

var parse=function(text) {
  scan(text);
  console.log('text=%s', text);
  console.log('tokens=%j', tokens);
  E();
}

var E=function() { // E=T ([+-] T)*
  push('E');
  T();
  while (isNext(/[\+\-]/)) {
    next(/[\+\-]/);
    T();
  }
  pop('E');
}

var T=function() { // T=F ([*/] F)*
  push('T');
  F();
  while (isNext(/[\*\/]/)) {
    next(/[\*\/]/);
    F();
  }
  pop('T')
}

var reNumber = /\d+/;
var reId = /[a-zA-Z]\w*/;

var F=function() {  // F=NUMBER | ID | ( E )
  push('F')
  if (isNext('(')) {
    next('(');
    E();
    next(')');
  } else if (isNext(reNumber)) {
    next(reNumber);
  } else if (isNext(reId)) {
    next(reId);
  } else {
    error('not F=NUMBER | ID | (E)')
  }
  pop('F')
}

parse('32+5*(182+degree*4-20)')
// parse('+++32+5*(182+degree*4-20)')
