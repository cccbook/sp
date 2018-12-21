#include <stdio.h>

int s, n, i;

int sum() {
  s = 0;
  i = ;
  while (i <= n) {
    s = s + i;
    i = i + 1;
  }
  return s;
}

int main() {
  n = 10;
  s = sum();
  printf("s=%d\n", s);
}
