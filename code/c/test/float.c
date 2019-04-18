#include <stdio.h>

int main () {
   float f=3.14159;
   printf("%08X=%f\n", *(int*) &f, f);
}