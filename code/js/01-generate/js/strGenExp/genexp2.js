<<<<<<< HEAD
var R = require('./random')

/*
E = N | E [+/-*] E
N = 0-9
*/

function E() {
  var gen = R.randSelect(["N", "EE"]);
  if (gen  === "N") {
      return N();
  } else {
      return E() + R.randSelect(["+", "-", "*", "/"]) + E();
  } 
}

function N() {
  return R.randSelect(["1", "2", "3", "4", "5", "6", "7", "8", "9"]);
}

var e = E();
console.log(e, "=", eval(e));
=======
/*
E = T | ( E [+/-*] E )
T = 0-9
*/
var U = require('./util')

function E () {
  if (Math.random() < 0.5) {
    return T()
  } else {
    return '(' + E() + U.randSelect(['+', '-', '*', '/']) + E() + ')'
  }
}

function T () {
  return U.randSelect(['1', '2', '3', '4', '5', '6', '7', '8', '9']);
}

var e = E()
console.log(e, '=', eval(e))
>>>>>>> 2dd7d214933c9abc3a7c06188eba934cc62c7d04
