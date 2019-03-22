#ifndef __LEXER_H__
#define __LEXER_H__

#include "util.h"

typedef enum { Id, Int, Keyword, Literal, Op } TokenType;

extern char *typeName[];
extern char code[];
extern char strTable[], *strTableEnd;
extern char *tokens[], tokenTop, tokenIdx;
extern TokenType types[];

extern int lex(char *text);
extern void lexDump();

#endif