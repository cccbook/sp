#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "util.h"

Pair macroList[] = {
  {"iput", "@0;swi"},
  {"cput", "@1;swi"},
  {"sputi","@%s;D=A;@2;swi"},
  {"sput", "@%s;D=A;@3;swi"},
  {"fput", "@18;swi"},
  {"fset", "@%s;D=A;@16;swi"},
  {"fadd", "@%s;D=A;@19;swi"},
  {"fsub", "@%s;D=A;@20;swi"},
  {"fmul", "@%s;D=A;@21;swi"},
  {"fdiv", "@%s;D=A;@22;swi"},
};

Map macroMap;

int expand(char *line, char *code) {
  replace(line, "\r\n", ' ');
  printf("line=%s\n", line);
  if (line[0] != '.') { sprintf(code, "%s\n", line); return 0; }
  char *p = line + 1, fname[SMAX], arg[SMAX];
  sscanf(p, "%s %s", fname, arg);
  char *macro = mapLookup(&macroMap, fname);
  char eMacro[TMAX];
  sprintf(eMacro, macro, arg);
  sprintf(code, "// %s\n%s\n", line, eMacro);
  // printf("macro=%s arg=%s code=\n%s\n", macro, arg, code);
  replace(code, ";", '\n');
  return 1;
}

int macroExpand(char *iFile, char *oFile) {
  char line[SMAX];
  printf("iFile=%s oFile=%s\n", iFile, oFile);
  FILE *iF = fopen(iFile, "r");
  FILE *oF = fopen(oFile, "w");
  while (fgets(line, sizeof(line), iF)) {
    char code[TMAX];
    expand(line, code);
    printf("%s", code);
    fwrite(code, strlen(code), 1, oF);
  }
  fclose(iF);
  fclose(oF);
}

// run: ./macro <file> 
// notice : <file> with no extension.
int main(int argc, char *argv[]) {
  char *file = argv[1];
  char iFile[SMAX], oFile[SMAX];
  sprintf(iFile, "%s.m", file);
  sprintf(oFile, "%s.asm", file);

  mapNew(&macroMap, 37); mapAddAll(&macroMap, macroList, ARRAY_SIZE(macroList));
  macroExpand(iFile, oFile);
  mapFree(&macroMap);
}