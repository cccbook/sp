#include <stdio.h>

extern int fib(int n);

int main() {
  int t = fib(10);
  printf("fib(10)=%d\n", t);
}