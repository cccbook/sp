#ifndef __COMPILER_H__
#define __COMPILER_H__

#include "lexer.h"
#include "ir.h"

extern char *typeName[];

extern char code[];
extern char strTable[], *strTableEnd;
extern char *tokens[], tokenTop, tokenIdx;
extern int types[];

extern void parse();

#endif