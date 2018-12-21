const acorn = require("acorn")
const walk = require("acorn-walk")

walk.full(acorn.parse("1 + 1"), node => {
  console.log(`There's a ${node.type} node at ${node.value}`)
  console.log('node=', node)
})