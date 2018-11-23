var U = require('./util')
var next = U.print
var p = U.probability

// === BNF Grammar =====
// StmtList = Stmt+
// Stmt = While | Assign
// While = while '(' Exp ')' { StmtList }
// Assign = id '=' Exp
// Exp = T ([+-] T)?
// T = F ([*/] F)?
// F = [0-9a-cx-z] | (Exp)

var level = 0

function indent() {
  next(''.padStart(level * 2))
}

function StmtList () {
  do {
    Stmt()
  } while (p(0.5))
}

function Stmt () {
  if (p(0.5)) {
    While()
  } else {
    indent(); Assign()
  }
}

function While () {
  indent(); next('while ('); Exp(); next(') {\n')
  level ++; StmtList(); level --
  indent(); next('}\n')
}

function Assign () {
  id(); next('='); Exp(); next('\n')
}

var idList = ['x', 'y', 'z', 'a', 'b', 'c']

function id () {
  next(U.randSelect(idList))
}

function Exp () {
  T()
  if (p(0.5)) {
    next(U.randChar('+-'))
    T()
  }
}

function T () {
  F()
  if (p(0.5)) {
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

While()
