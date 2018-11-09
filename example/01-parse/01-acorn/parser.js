const acorn = require("acorn")

// const code = "1 + 1"
const code = "function f(a,b) { return a + b }"

console.log(acorn.parse(code))

/*
const walk = require("acorn-walk")
walk.simple(acorn.parse(code), {
  Program(node) {
    console.log(node)
  }
})
*/