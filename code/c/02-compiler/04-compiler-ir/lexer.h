#ifndef __LEXER_H__
#define __LEXER_H__

#include "util.h"

enum { Id, Int, Keyword, Literal, Char };

extern int lex(char *text);

#endif