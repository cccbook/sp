#include <stdio.h>

int total(int *a, int size) {
  int s = 0, i = 0;
  while (i < size) {
    s = s + *a;
    a ++;
  }
  return s;
}

int main() {
  int *array;
  int t = total(array, 5);
  printf("t=%d\n", t);
}
