#ifndef __LEXER_H__
#define __LEXER_H__

#include "util.h"

enum { Id, Keyword, Type, Number, Literal, Char, End };

extern char *typeName[];

extern char token[];
extern int line, pos, type, tokenIdx;
extern char *start, *lineBegin;

#define isDigit(ch) ((ch) >= '0' && (ch) <='9')

#define isAlpha(ch) (((ch) >= 'a' && (ch) <='z') || ((ch) >= 'A' && (ch) <= 'Z'))

extern void lexInit();
extern char *lexScan();
extern void lex(char *code);

#endif
