#include "map.h"

Pair jList[] = {
  {"",   "000"}, {"JGT","001"}, {"JEQ","010"}, {"JGE","011"},
  {"JLT","100"}, {"JNE","101"}, {"JLE","110"}, {"JMP","111"}
};

Map jMap;

int main() {
  mapNew(&jMap, 17);
  jMap.table = jList;
  jMap.top = 8;
  char *jCode = mapLookup(&jMap, "JLE");
  printf("jCode=%s\n", jCode);
}

