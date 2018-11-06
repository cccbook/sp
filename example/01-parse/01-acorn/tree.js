const acorn = require("acorn")
const walk = require("acorn-walk")

// const code = "1 + 1"
const code = "function f(a,b) { return a + b }"

walk.simple(acorn.parse(code), {
  Program(node) {
    console.log(node)
  }
})