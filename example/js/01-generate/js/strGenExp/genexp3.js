/*
E = T | (T [+ -] T)
T = F | (F [* /] F )
F = 0-9 | '(' E ')'
*/
var U = require('./util')

function E () {
  if (Math.random() < 0.5) {
    return T()
  } else {
    return T() + U.randSelect(['+', '-']) + T()
  }
}

function T () {
  if (Math.random() < 0.5) {
    return F()
  } else {
    return F() + U.randSelect(['*', '/']) + F()
  }
}

function F () {
  if (Math.random() < 0.5) {
    return U.randSelect(['1', '2', '3', '4', '5', '6', '7', '8', '9'])
  } else {
    return '(' + E() + ')'
  }
}

var e = E()
console.log(e, '=', eval(e))
