#ifndef __STRTABLE_H__
#define __STRTABLE_H__

#include <string.h>

typedef struct {
  char *text, *end;
} StrTable;

// #define stPrint(...) ({ char stTemp[SMAX]; sprintf(stTemp, __VA_ARGS__); char *p=stAdd(stTemp); p; })
extern void stNew(StrTable *table, char *text);
extern char *stAdd(StrTable *table, char *str);
extern int stSize(StrTable *table);

#endif
