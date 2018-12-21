#include "rlib.c"

// === EBNF Grammar =====
// S = NP VP
// NP = DET N
// VP = V NP
// N = dog | cat
// V = chase | eat
// DET = a | the

char* n[] = {"dog", "cat"};
char* v[] = {"chase", "eat"};
char* det[] = {"a", "the"};

void N() {
  printf("%s", randSelect(n, 2));
}

void V() {
  printf("%s", randSelect(v, 2));
}

void DET() {
  printf("%s", randSelect(det, 2));
}

void NP() {
  DET();
  printf(" ");
  N();
}

void VP() {
  V();
  printf(" ");
  NP();
}

void S() {
  NP();
  printf(" ");
  VP();
  printf("\n");
}

int main() {
  timeSeed();
  S();
}

