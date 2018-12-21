#ifndef __ANALYZER_H__
#define __ANALYZER_H__

#include <assert.h>
#include "strTable.h"
#include "lexer.h"

#define isEnd() (type == End)
#define error(...) ({ char tline[SMAX]; sscanf(lineBegin, "%[^\n]*", tline); printf("line %d pos %d\ncode: %s\n-- ", line, pos, tline); printf( __VA_ARGS__); assert(0); })
extern void scanInit(char *code);
extern int  isNext(char *set);
extern int  isNextType(int checkType);
extern char *next();
// extern void error(char *filter);
extern char *skipType(int checkType);
extern char *skip(char *set);

#endif
