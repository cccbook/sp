int a, b, c;

int sum(int n) {
  int s=0, i=1, j=2, k=3, l=4;
  s = 0;
  i = 1;
  while (i <= n) {
    s = s + i;
    i = i + 1;
  }
  return s;
}
