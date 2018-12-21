#include <stdio.h>
#include <unistd.h>

int main() {
  int m = 100;
  printf("before fork\n");
  int n = fork();
  if (n>0) {
    printf("I am parent process!\n");
    printf("m=%d n=%d\n", m, n);
  } else {
    printf("I am child process!\n");
    printf("m=%d n=%d\n", m, n);
  }
  return 0;
}
