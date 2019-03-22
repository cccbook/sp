#include "compiler.h"

int readText(char *fileName, char *text, int size) {
  FILE *file = fopen(fileName, "r");
  int len = fread(text, 1, size, file);
  text[len] = '\0';
  fclose(file);
  return len;
}

int dump(char *strTable[], int top) {
  printf("========== dump ==============\n");
  for (int i=0; i<top; i++) {
    printf("%d:%s\n", i, strTable[i]);
  }
}

int main(int argc, char * argv[]) {
  int isDump = 0, isRun = 0, isLexDump = 0;
  for (int i=0; i<argc; i++) {
    if (eq(argv[i], "-l")) isLexDump = 1;
    if (eq(argv[i], "-d")) isDump = 1;
    if (eq(argv[i], "-r")) isRun = 1;
  }
  readText(argv[1], code, TMAX);
  // puts(code);
  lex(code);
  if (isLexDump) lexDump();
  parse();
  if (isDump) irDump();
  if (isRun) irRun();
}