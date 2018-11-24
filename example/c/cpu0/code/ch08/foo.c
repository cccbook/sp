extern foo(int x, int y);

int f(int a, int b, int c) {
  if (foo(a+b, c))
    c = b++/a;
  return c;
}
