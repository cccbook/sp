#include "lexer.h"

char *typeName[6] = {"Id", "Keyword", "Type", "Number", "Literal", "Char"};
char token[SMAX];
int  line, pos, type, tokenIdx;
char *p, *start, *lineBegin;

void lexInit(char *code) {
  p = code;
  lineBegin = code;
  tokenIdx = 0;
  line = 1;
}

char *lexScan() {
  type = Char;
  while (1) {
    start = p;
    if (isspace(*p)) { // 忽略空白
      while (isspace(*p)) {
        if (*p == '\n') {
          lineBegin = p+1;
          line ++;
        }
        p++;
      }
      continue;
    } else if (*p == '/') {
      p++;
      if (*p == '/') { // 忽略註解 //...
        while (*p != '\n') p++;
        continue;
      }
    } else if (*p == '\0') { // 結束了
      type = End;
    } else if (*p == '"') { // 字串
      p++;
      while (*p != '"') p++;
      p++;
      type = Literal;
    } else if (*p >='0' && *p <='9') { // 數字
      while (*p >='0' && *p <='9') p++;
      type = Number;
    } else if (isAlpha(*p) || *p == '_') { // 變數名稱或關鍵字
      while (isAlpha(*p) || isDigit(*p) || *p == '_') p++;
      type = Id;
    } else if (strchr("<>!=", *p) != NULL) {
      p++;
      if (*p == '=') p++; // <=, >=, != ==
    } else if (strchr("+-&|", *p) != NULL) {
      char op = *p++;
      if (*p == op) p++;  // ++ -- && ||
    } else {
      p++;
    }
    int len = p-start;
    strncpy(token, start, len);
    token[len] = '\0';
    if (isMember(token, "var int char")) type = Type;
    pos = p - lineBegin;
    tokenIdx++;
    return token;
  }
}

void lex(char *code) {
  printf("================= lex =================\n");
  lexInit(code);
  while (1) {
    char *tok = lexScan();
    if (*tok == '\0') break;
    printf("%04d:%-10s line=%d pos=%d type=%s\n", tokenIdx, token, line, pos, typeName[type]);
  }
}
