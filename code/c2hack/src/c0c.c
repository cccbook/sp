#include "compiler.h"

char code[TMAX];

int main(int argc, char * argv[]) {
  argHandle(argc, argv, 2, "c0c <file> -d -r");
  char c0File[SMAX], irFile[SMAX], m0File[SMAX];
  sprintf(c0File, "%s.c0", argv[1]);
  sprintf(irFile, "%s.i0", argv[1]);
  sprintf(m0File, "%s.m0", argv[1]);
  readText(c0File, code, TMAX);
  // lex(code);
  // if (isDebug) lexDump();
  parse(code);
  irPass2();
  if (isDebug) irDump();
  irSave(irFile);
  ir2m0(m0File);
  if (isFlag['r']) irRun();
}