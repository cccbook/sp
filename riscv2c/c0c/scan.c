#include "scan.h"

void scanInit(char *code) {
  lexInit(code);
}

int isNext(char *set) {
  return isMember(token, set);
}

int isNextType(int checkType) {
  return (*token != '\0' && type == checkType);
}

char *next() {
  char *t = stAdd(token);
  lexScan();
  return t;
}

/*
void error(char *filter) {
  printf("expect %s got %s fail!\n", filter, token);
  printf("-- line: %d pos: %d\n", line, pos);
  char errorCode[SMAX];
  strncpy(errorCode, start, SMAX-1);
  errorCode[SMAX-1] = '\0';
  printf("-- error code: %s\n", errorCode);
  assert(0);
}
*/

char *skipType(int checkType) {
  // if (type != checkType) error(typeName[checkType]);
  if (type != checkType) error("expect %s got %s fail!\n", typeName[checkType], token);
  return next();
}

char *skip(char *set) {
  // if (!isNext(set)) error(set);
  if (!isNext(set)) error("expect %s got %s fail!\n", set, token);
  return next();
}
