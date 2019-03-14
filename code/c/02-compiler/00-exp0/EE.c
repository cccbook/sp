#include <stdio.h>
void F();

void E() {
  printf("E started");
  E();
  F();
  printf("E finished");
}

void F() {

}

int main() {
  E();
}
