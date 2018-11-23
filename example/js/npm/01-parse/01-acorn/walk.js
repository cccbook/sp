const acorn = require("acorn")
const walk = require("acorn-walk")

const code = "function f(a,b) { return a + b }"

walk.simple(acorn.parse(code), {
  FunctionDeclaration(node) {
    console.log(node.id.name)
  }
})
