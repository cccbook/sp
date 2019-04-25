#include <stdio.h>

int f(int n) {
  if (n==1) {
    return 2;
  } else {
    printf("n=%d ", n);
    int r = 2 * f(n-1);
    printf("r=%d\n", r);
    return r;
  }
}

int main() {
  printf("f(5)=%d\n", f(5));
}