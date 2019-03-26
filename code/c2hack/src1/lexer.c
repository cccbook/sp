#include "lexer.h"

char *typeName[5] = {"Id", "Int", "Keyword", "Literal", "Op"};
char code[TMAX], *p;
char sTable[TMAX], *sTableEnd=sTable;
char *tokens[TMAX], token[SMAX];
int tokenTop=0, tokenIdx=0;
TokenType types[TMAX], type;

char *scan() {
  while (isspace(*p)) p++;

  char *start = p;
  if (*p == '\0') return NULL;
  if (*p == '"') {
    p++;
    while (*p != '"') p++;
    p++;
    type = Literal;
  } else if (*p >='0' && *p <='9') { // 數字
    while (*p >='0' && *p <='9') p++;
    type = Int;
  } else if (isalpha(*p) || *p == '_') { // 變數名稱或關鍵字
    while (isalpha(*p) || isdigit(*p) || *p == '_') p++;
    type = Id;
  } else if (strchr("+-*/%%&|<>!=", *p) >= 0) {
    char c = *p++;
    if (*p == '=') p++; // +=, ==, <=, !=, ....
    else if (strchr("+-&|", c) >= 0 && *p == c) p++; // ++, --, &&, ||
    type = Op;
  } else {
    p++;
    type = Op;
  }

  int len = p-start;
  strncpy(token, start, len);
  token[len] = '\0';
  return token;
}

void lex(char *code) {
  p = code;
  tokenTop = 0;
  while (1) {
    char *tok = scan();
    if (tok == NULL) break;
    strcpy(sTableEnd, tok);
    types[tokenTop] = type;
    tokens[tokenTop++] = sTableEnd;
    sTableEnd += (strlen(tok)+1);
  }
}

void lexDump() {
  printf("========== lexDump ==============\n");
  for (int i=0; i<tokenTop; i++) {
    printf("%02d:%-20s %-20s\n", i, tokens[i], typeName[types[i]]);
  }
}