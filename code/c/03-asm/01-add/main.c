#include <stdio.h>

extern int add(int a, int b);

int main() {
  int t = add(5, 8);
  printf("add(5, 8)=%d\n", t);
}