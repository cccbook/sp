#include <string.h>
#include <stdio.h>

int main () {
   // char str[80] = "D=A+1;JMP";
   char str[80] = "A+1;JMP";
   char *d = strtok(str, "=");
   printf("d=%s\n", d);
}