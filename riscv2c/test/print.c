#include <stdio.h>

int n;

int main() {
  n = 7;
  if (n > 5) {
    printf("n>5\n");
    // return 7;
  } else {
    printf("n<=5\n");
  }
  printf("Hello %d!\n", n);
  return 8;
}
