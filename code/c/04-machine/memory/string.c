#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char str[]="hello!";
  char temp[100]="xxxxxxxxxxxxxxxxxxxxx";
  strncpy(temp, str, strlen(str));
  // temp[strlen(str)] = '\0';
  printf("%s\n", temp);
}
