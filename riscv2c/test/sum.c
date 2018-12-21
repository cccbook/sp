#include <stdio.h>

int sum(int n) {
  int s = 0, i = 1;
  printf("i=%d s=%d n=%d\n", i, s, n);
  while (i <= n) {
    s = s + i;
    printf("i=%d s=%d\n", i, s);
    i = i + 1;
  }
  return s;
}

int main() {
  // int total = sum(10);
  // printf("sum(10)=%d\n", total);
  printf("sum(10)=%d\n", sum(10));
}
