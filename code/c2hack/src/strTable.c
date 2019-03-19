
#include "strTable.h"

void stNew(StrTable *table, char *text) {
  table->text = table->end = text;
}

char *stAdd(StrTable *table, char *str) {
  char *p = table->end;
  strcpy(p, str);
  table->end += (strlen(str)+1);
  return p;
}

int stSize(StrTable *table) {
  return table->end - table->text;
}