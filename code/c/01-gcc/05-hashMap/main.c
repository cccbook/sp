#include "map.h"

Pair jList[] = {
  {"",   "000"}, {"JGT","001"}, {"JEQ","010"}, {"JGE","011"},
  {"JLT","100"}, {"JNE","101"}, {"JLE","110"}, {"JMP","111"}
};

Map jMap;

int main() {
  printf("======= main() ==============\n");
  mapNew(&jMap, 17);
  for (int i=0; i<8; i++) {
    printf("%d : key=%s value=%s\n", i, jList[i].key, jList[i].value);
    mapAdd(&jMap, jList[i].key, jList[i].value);
  }
  mapDump(&jMap);
  char *jCode = mapLookup(&jMap, "JLE");
  printf("jCode=%s\n", jCode);
}

