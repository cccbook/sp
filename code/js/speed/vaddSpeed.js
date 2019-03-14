function add(a, b) {
  return a+b
}

function vadd1(a, b) {
  let len = a.length
  let c = new Array(len)
  for (let i=0; i<len; i++) {
    c[i] = a[i] + b[i]
  }
  return c
}

function vadd2(a, b) {
  let len = a.length
  let c = new Array(len)
  for (let i=0; i<len; i++) {
    c[i] = add(a[i], b[i])
  }
  return c
}

function buildOp(op) {
  let text = `
  let len = a.length
  let c = new Array(len)
  for (let i=0; i<len; i++) {
    c[i] = ${op}
  }
  return c
  `
  return new Function('a', 'b', text)
}

let vadd3 = buildOp('a[i]+b[i]')

function vadd4(a,b) {
  let code = `
  let len = a.length
  let c = new Array(len)
  for (let i=0; i<len; i++) {
    c[i] = a[i]+b[i]
  }
  c
  `
  return eval(code)
}

function randn(n) {
  let a = []
  for (let i=0; i<n; i++) a.push(Math.random()*100)
  return a
}

function loops(n, f, a, b, fname) {
  let start = Date.now()
  for (let i=0; i<n; i++) {
    f(a,b)
  }
  let finished = Date.now()
  console.log(`${fname} time:${finished-start} ms`)
}
let a = randn(100000)
let b = randn(100000)

loops(1000, vadd1, a, b, 'vadd1')
loops(1000, vadd2, a, b, 'vadd2')
loops(1000, vadd3, a, b, 'vadd3')
loops(1000, vadd4, a, b, 'vadd4')
