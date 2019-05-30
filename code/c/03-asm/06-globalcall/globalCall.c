#include <stdio.h>

int a=5, b=8, c=1;

void add() {
   c = a + b;
}

int main() {
  add();
  printf("add(5, 8)=%d\n", c);
  return 0;
}