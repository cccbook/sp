var R = require('./random')

// === BNF Grammar =====
// E = T [+-*/] E | T
// T = [0-9] | (E)

function print(s) {
  process.stdout.write(s);
}

function E() {
  if (R.randInt(1,10) <= 5) {
      T(); print(R.randChar("+-*/")); E();
  } else {
      T();
  }
}

function T() {
  if (R.randInt(1,10) < 7) {
      print(R.randChar("0123456789"));
  } else {
      print("("); E(); print(")");
  }
}

for (var i=0; i<10; i++) {
  E();
  print("\n");
}