#include "compiler.h"

int main(int argc, char * argv[]) {
  int isLexDump = 0, isIrDump = 0, isRun = 0;
  for (int i=0; i<argc; i++) {
    if (eq(argv[i], "-lex")) isLexDump = 1;
    if (eq(argv[i], "-ir")) isIrDump = 1;
    if (eq(argv[i], "-run")) isRun = 1;
  }
  readText(argv[1], code, TMAX);
  lex(code);
  if (isLexDump) lexDump();
  parse();
  irPass2();
  if (isIrDump) irDump();
  if (isRun) irRun();
}