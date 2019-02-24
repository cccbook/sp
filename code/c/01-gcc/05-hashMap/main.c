#include "map.h"

Pair jList[] = {
  {"",   "000"}, {"JGT","001"}, {"JEQ","010"}, {"JGE","011"},
  {"JLT","100"}, {"JNE","101"}, {"JLE","110"}, {"JMP","111"}
};

Map jMap;

int main() {
  mapNew(&jMap, 23);
  mapAddAll(&jMap, jList, ARRAY_SIZE(jList));
  mapDump(&jMap);
  char *jle = mapLookup(&jMap, "JLE");
  printf("jle=%s\n", jle);
  char *xxx = mapLookup(&jMap, "XXX");
  printf("xxx=%s\n", xxx);
  mapFree(&jMap);
}
