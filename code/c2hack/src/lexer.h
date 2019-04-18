#ifndef __LEXER_H__
#define __LEXER_H__

#include "../lib/util.h"
#include "../lib/strTable.h"

typedef enum { Id, Int, Keyword, Literal, Op, End } TokenType;

typedef struct {
  TokenType type;
  char *str;
} Token;

extern char *tokenTypeName[];
extern void lexInit(char *code);
extern Token lexScan();

#endif