#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
  pid_t self, parent;
  self = getpid();
  parent = getppid();
  printf("PID : %d, Parent PID:%d\n", (int) self, (int) parent);
  return 0;
}
