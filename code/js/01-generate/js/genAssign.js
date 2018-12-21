var U = require('./util')
var next = U.print

// === BNF Grammar =====
// Assign = id '=' Exp
// Exp = T ([+-] T)?
// T = F ([*/] F)?
// F = [0-9] | (Exp)

var idList = ['x', 'y', 'z', 'a', 'b', 'c']

function Assign () {
  id()
  next('=')
  Exp()
  next('\n')
}

function id () {
  next(U.randSelect(idList))
}

function Exp () {
  T()
  if (U.randInt(1, 10) <= 5) {
    next(U.randChar('+-'))
    T()
  }
}

function T () {
  F()
  if (U.randInt(1, 10) <= 5) {
    next(U.randChar('*/'))
    F()
  }
}

function F () {
  if (U.randInt(1, 10) < 7) {
    next(U.randChar('0123456789'))
  } else {
    next('(')
    Exp()
    next(')')
  }
}

for (var i = 0; i < 10; i++) {
  Assign()
}
