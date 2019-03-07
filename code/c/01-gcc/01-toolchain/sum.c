#include <stdio.h>

int sum(int n) {
  int s=0;
  for (int i=0; i<=n; i++) {
    s=s+i;
  }
  return s;
}

int main() {
  int t = sum(10);
  printf("sum(10)=%d\n", t);
}