const U = module.exports = {}

U.rand = function (a, b) {
  return a + Math.random() * (b - a)
}

U.randInt = function (a, b) {
  return Math.floor(a + Math.random() * (b - a))
}

U.randSelect = function (a) {
  return a[U.randInt(0, a.length)]
}

U.randChar = function (str) {
  var len = str.length
  var i = U.randInt(0, len - 1)
  return str[i]
}

U.print = function (s) {
  process.stdout.write(s)
}

U.probability = function (p) {
  return (Math.random() < p)
}
