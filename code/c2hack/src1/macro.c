#include <stdio.h>
#include <stdlib.h>
#include "../lib/map.h"
#include "../lib/util.h"

Pair macroList[] = {
  // io
  {"iputD","@0\nswi"},
  {"cputD","@1\nswi"},
  {"iput", "@${1}\nD=M\n@0\nswi"},
  {"cput", "@${1}\nD=M\n@1\nswi"},
  {"sput", "@${1}\nD=A\n@3\nswi"},
  // float
  {"fput", "@18\nswi"},
  {"fset", "@${1}\nD=A\n@17\nswi"},
  {"fadd", "@${1}\nD=A\n@19\nswi"},
  {"fsub", "@${1}\nD=A\n@20\nswi"},
  {"fmul", "@${1}\nD=A\n@21\nswi"},
  {"fdiv", "@${1}\nD=A\n@22\nswi"},
  // control
  {"set", "@${3}\nD=M\n@${1}\nM=D"}, // .set  i = t1
  {"setc","@${3}\nD=A\n@${1}\nM=D"}, // .setc i = 5
  {"op", "@${3}\nD=M\n@${5}\nD=D${4}M\n@${1}\nM=D"}, // .op z = x + y
  {"goto", "@${1}\n0;JMP"}, // goto L
  {"if", "@${1}\nD=M\n@${3}\nD;JNE"}, // if e goto L
  {"ifnot", "@${1}\nD=M\n@${3}\nD;JEQ"}, // ifnot e goto L

};

Map macroMap;

int expand(char *line, char *code) {
  replace(line, "\r\n", ' ');
  if (line[0] != '.') { sprintf(code, "%s\n", line); return 0; }
  char p[6][SMAX]; memset(p, 0, 6*SMAX);
  sscanf(line, ".%s %s %s %s %s %s", p[0], p[1], p[2], p[3], p[4], p[5]);
  char *macro = mapLookup(&macroMap, p[0]);
  if (!macro) error("macro %s not found!", p[0]);
  char eMacro[TMAX];
  format(eMacro, macro, p[1], p[2], p[3], p[4], p[5]);
  sprintf(code, "// %s\n%s\n", line, eMacro);
  return 1;
}

void macroExpand(char *iFile, char *oFile) {
  char line[SMAX];
  debug("====== macroExpand ============\n");
  FILE *iF = fopen(iFile, "r");
  FILE *oF = fopen(oFile, "w");
  while (fgets(line, sizeof(line), iF)) {
    char code[TMAX];
    int isExpand = expand(line, code);
    if (isExpand) { debug("%s", code); } else debug("%s", line);
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
  sprintf(iFile, "%s.m0", file);
  sprintf(oFile, "%s.s0", file);

  mapNew(&macroMap, 37); mapAddAll(&macroMap, macroList, ARRAY_SIZE(macroList));
  macroExpand(iFile, oFile);
  mapFree(&macroMap);
}