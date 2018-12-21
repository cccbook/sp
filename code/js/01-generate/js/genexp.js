var U = require('./util')
var next = U.print

// === BNF Grammar =====
// E = T [+-*/] E | T
// T = [0-9] | (E)

function E () {
  if (U.randInt(1, 10) <= 5) {
    T()
    next(U.randChar('+-*/'))
    E()
  } else {
    T()
  }
}

function T () {
  if (U.randInt(1, 10) < 7) {
    next(U.randChar('0123456789'))
  } else {
    next('(')
    E()
    next(')')
  }
}

for (var i = 0; i < 10; i++) {
  E()
  next('\n')
}
