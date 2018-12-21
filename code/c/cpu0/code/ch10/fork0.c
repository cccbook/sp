#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
  pid_t self, child;
  self = getpid();
  child = fork();
  if (child != 0) {
    printf("Parent process, PID:%d\n", (int) self);
    printf("Child process, PID:%d\n", (int) child);
  } else {
    printf("This is the child process. PID:%d\n", (int) getpid());
  }
  return 0;
}
