#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "util.h"

Pair macroList[] = {
  {"iputD","@0;swi"},
  {"cputD","@1;swi"},
  {"iput", "@%s;D=M;@0;swi"},
  {"cput", "@%s;D=M;@1;swi"},
  {"sput", "@%s;D=A;@3;swi"},
  {"fput", "@18;swi"},
  {"fset", "@%s;D=A;@17;swi"},
  {"fadd", "@%s;D=A;@19;swi"},
  {"fsub", "@%s;D=A;@20;swi"},
  {"fmul", "@%s;D=A;@21;swi"},
  {"fdiv", "@%s;D=A;@22;swi"},
};

Map macroMap;

int expand(char *line, char *code) {
  replace(line, "\r\n", ' ');
  if (line[0] != '.') { sprintf(code, "%s\n", line); return 0; }
  char *p = line + 1, fname[SMAX], arg[SMAX];
  sscanf(p, "%s %s", fname, arg);
  char *macro = mapLookup(&macroMap, fname);
  char eMacro[TMAX];
  sprintf(eMacro, macro, arg);
  sprintf(code, "// %s\n%s\n", line, eMacro);
  replace(code, ";", '\n');
  return (macro != NULL);
}

int macroExpand(char *iFile, char *oFile) {
  char line[SMAX];
  debug("====== macroExpand ============\n");
  FILE *iF = fopen(iFile, "r");
  FILE *oF = fopen(oFile, "w");
  while (fgets(line, sizeof(line), iF)) {
    char code[TMAX];
    int isExpand = expand(line, code);
    if (isExpand) debug("%s", code); else debug("%s", line);
    fwrite(code, strlen(code), 1, oF);
  }
  fclose(iF);
  fclose(oF);
}

// run: ./macro <file> 
// notice : <file> with no extension.
int main(int argc, char *argv[]) {
  argHandle(argc, argv, 2, "./macro <file>\n");

  char *file = argv[1];
  char iFile[SMAX], oFile[SMAX];
  sprintf(iFile, "%s.m", file);
  sprintf(oFile, "%s.asm", file);

  mapNew(&macroMap, 37); mapAddAll(&macroMap, macroList, ARRAY_SIZE(macroList));
  macroExpand(iFile, oFile);
  mapFree(&macroMap);
}