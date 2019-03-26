#ifndef __LEXER_H__
#define __LEXER_H__

#include "../lib/util.h"

typedef enum { Id, Int, Keyword, Literal, Op } TokenType;

extern char *typeName[];
extern char code[];
// extern char strTable[], *strTableEnd;
extern char *tokens[];
extern int tokenTop, tokenIdx;
extern TokenType types[];

extern void lex(char *text);
extern void lexDump();

#endif