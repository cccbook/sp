#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int spawn(char *prog, char *const arg_list[]) {
  pid_t child;
  child = fork();
  if (child != 0) {
    return child;
  } else {
    execvp(prog, arg_list);
	fprintf(stderr, "spawn error\n");
    return -1;
  }
}

int main() {
  char *arg_list[] = { "ls", "-l", "/etc", NULL };
  spawn("ls", arg_list);
  printf("The end of program.\n");
  return 0;
}
