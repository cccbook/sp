
#include "strTable.h"

char strTable[1000*1000], *strTableEnd = strTable;

void stInit() {
  strTableEnd = strTable;
}

char *stAdd(char *str) {
  char *strPtr = strTableEnd;
  strcpy(strTableEnd, str);
  strTableEnd += (strlen(str)+1);
  return strPtr;
}
