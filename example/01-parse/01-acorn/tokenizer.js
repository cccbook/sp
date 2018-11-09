const acorn = require("acorn")
let code = "function f(a,b) { return a + b }"
// let code = '1 + 1'
let tokens = [...acorn.tokenizer(code)];

console.log(tokens)