#include <stdio.h>

int s, i, n;

int sum() {
  s=0;
  i=1;
  while (i <= n) {
    s = s + i;
    i++;
  }
  return s;
}

int main() {
  n=10;
  printf("sum(%d)=%d\n", n, sum());
}