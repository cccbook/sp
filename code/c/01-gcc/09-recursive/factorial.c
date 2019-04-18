#include <stdio.h>

int factorial(int n) {
  if (n==1) return 1;
  printf("n=%d ", n);
  int r = n * factorial(n-1);
  printf("r=%d\n", r);
  return r;
}

int main() {
  printf("factorial(5)=%d\n", factorial(5));
}
