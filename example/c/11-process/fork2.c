#include <stdio.h>
#include <unistd.h>

int main() {
  int n = fork();
  if (n>0) {
    printf("I am parent process!\n");
  } else {
    printf("I am child process!\n");
  }
  return 0;
}
