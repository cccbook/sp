#include <stdio.h>

extern int sum(int n);

int main() {
  int t = sum(10);
  printf("sum(10)=%d\n", t);
}