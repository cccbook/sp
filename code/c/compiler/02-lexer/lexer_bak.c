#include <stdio.h>
#include <string.h>

#define TMAX 10000000
#define SMAX 100000


enum { Id, Int, Keyword, Literal, Char };

char *typeName[5] = {"Id", "Int", "Keyword", "Literal", "Char"};

char *p; // 目前掃描到的位置
// char token[100];
// int  type;
char code[TMAX];
char strTable[TMAX], *strp;

struct Symbol {
  char *name;
  int id;
  int type;
} Symbol

char *symTable[SMAX];


#define isDigit(ch) ((ch) >= '0' && (ch) <='9')

#define isAlpha(ch) (((ch) >= 'a' && (ch) <='z') || ((ch) >= 'A' && (ch) <= 'Z'))

int readText(char *fileName, char *text, int size) {
  FILE *file = fopen(fileName, "r");
  int len = fread(text, 1, size, file);
  text[len] = '\0';
  fclose(file);
  return len;
}

char *next() {
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
  } else if (isAlpha(*p) || *p == '_') { // 變數名稱或關鍵字
    while (isAlpha(*p) || isDigit(*p) || *p == '_') p++;
    type = Id;
  } else { // 單一字元
    p++;
    type = Char;
  }
  int len = p-start;

  strncpy(token, start, len);
  token[len] = '\0';
  return token;
}

int lex(char *fileName) {
  p = code;
  while (1) {
    if (next() == NULL) break;
    printf("%-10s %-10s\n", typeName[type], token);
  }
}

int main(int argc, char * argv[]) {
  readText(argv[1], code, sizeof(code));
  puts(code);
  lex(code);
}

