int a=3, b=5;
int add, sub, mul, div, band, bor, bxor, bnot, land, lor, lnot, eq, neq, gt, lt, ge, le;
void op() {
  add = a + b;
  sub = a - b;
  mul = a * b;
  div = a / b;
  band = a & b;
  bor  = a | b;
  bxor = a ^ b;
  bnot = ~a;
  land = a && b;
  lor  = a || b;
  lnot = !a;
  eq   = a == b;
  neq  = a != b;
  gt   = a >  b;
  lt   = a <  b;
  ge   = a >= b;
  le   = a <= b;
}