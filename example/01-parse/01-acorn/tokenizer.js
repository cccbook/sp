const acorn = require("acorn")
let str = '1 + 1'
let tokens = [...acorn.tokenizer(str)];

console.log(tokens)