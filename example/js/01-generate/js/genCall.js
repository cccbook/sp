var U = require('./util')
var next = U.print
var p = U.probability

// === BNF Grammar =====
// Stmt = While | Assign
// While = while Exp { Stmt+ }
// Assign = id '=' (Exp | Call)
// Call = fname '(' exp* ')'
// Exp = T ([+-] T)?
// T = F ([*/] F)?
// F = [0-9a-cx-z] | (Exp)

var level = 0

function indent() {
  next(''.padStart(level * 2))
}

function repeats (f, from=0, prob=0.5) {
  for (let i=0; i<from; i++) f()
  do {
    f()
  } while (p(prob))
}

function Stmt () {
  if (p(0.2)) {
    While()
  } else {
    indent(); Assign()
  }
}

function While () {
  indent(); next('while ('); Exp(); next(') {\n')
  level ++; repeats(Stmt, 1); level --
  indent(); next('}\n')
}

function Assign () {
  id()
  next('=') 
  if (p(0.7)) {
    Exp()
  } else {
    Call()
  }
  next('\n')
}

function Call () { // call a function
  next(U.randSelect(['run', 'get', 'apply'])); next('('); repeats(Exp, 0); next(')')
}

var idList = ['x', 'y', 'z', 'a', 'b', 'c']

function id () {
  next(U.randSelect(idList))
}

function Exp () {
  T()
  if (p(0.4)) {
    next(U.randChar('+-'))
    T()
  }
}

function T () {
  F()
  if (p(0.4)) {
    next(U.randChar('*/'))
    F()
  }
}

function F () {
  if (p(0.7)) {
    next(U.randChar('0123456789abcxyz'))
  } else {
    next('('); Exp(); next(')')
  }
}

repeats(Stmt, 1)
