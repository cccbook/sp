#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
  char *arg_list[] = { "ls", "-l", "/etc", NULL };
  execvp("ls", arg_list);
  printf("The end of program.\n");
}
