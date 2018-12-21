var ti = 0
var text

function lex(pText) {
  text = pText
  while (true) {
    let token = next()
    if (token == null) break
    console.log('token=', token)
  }
}

function next () {
  if (ti >= text.length) return null
  let c = text[ti]
  let token = []
  if (isDigit(text[ti])) {
    while (isDigit(text[ti])) {
      token.push(text[ti++])
    }
    return token.join('')
  }
  if ('+-'.indexOf(c) >=0) {
    while (text[ti] === c) {
      token.push(text[ti++])
    }
    return token.join('')
  }
  if (isIdLetter(c)) {
    while (isIdLetter(text[ti])) {
      token.push(text[ti++])
    }
    return token.join('')
  }
  return text[ti++]
}

function isDigit(c) {
  return c >= '0' && c <= '9'
}

function isOp2(c) {
  return '+-'.indexOf(c) >= 0
}

function isIdLetter(c) {
  return c.match(/[a-z0-9_]/i);
}

var code = "function sum(n) { var s, i; for (i=0; i<10; i++) { s = s+i } return s }";
lex(code)