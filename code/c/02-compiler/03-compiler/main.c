#include "compiler.h"

int readText(char *fileName, char *text, int size) {
  FILE *file = fopen(fileName, "r");
  int len = fread(text, 1, size, file);
  text[len] = '\0';
  fclose(file);
  return len;
}

void dump(char *strTable[], int top) {
  printf("========== dump ==============\n");
  for (int i=0; i<top; i++) {
    printf("%d:%s\n", i, strTable[i]);
  }
}

int main(int argc, char * argv[]) {
  readText(argv[1], code, TMAX);
  puts(code);
  lex(code);
  dump(tokens, tokenTop);
  parse();
  return 0;
}