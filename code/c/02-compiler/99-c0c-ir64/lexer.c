#include "lexer.h"

char *typeName[5] = {"Id", "Int", "Keyword", "Literal", "Op"};
char code[TMAX], *p;
char strTable[TMAX], *strTableEnd=strTable;
char *tokens[TMAX], tokenTop=0, tokenIdx=0, token[SMAX];
TokenType types[TMAX], type;

char *scan() {
  while (isspace(*p)) p++;

  char *start = p;
  // TokenType type;
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

int lex(char *code) {
  // printf("========== lex ==============\n");
  p = code;
  tokenTop = 0;
  while (1) {
    char *tok = scan();
    if (tok == NULL) break;
    strcpy(strTableEnd, tok);
    types[tokenTop] = type;
    tokens[tokenTop++] = strTableEnd;
    strTableEnd += (strlen(tok)+1);
    // printf("token=%s\n", tok);
  }
}

void lexDump() {
  printf("========== lexDump ==============\n");
  for (int i=0; i<tokenTop; i++) {
    printf("%02d:%-20s %-20s\n", i, tokens[i], typeName[types[i]]);
  }
}