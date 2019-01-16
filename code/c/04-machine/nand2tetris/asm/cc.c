#include <stdio.h>
#include <string.h>
#include "c6.c"

enum { Id, Int, Keyword, Literal, Char, None };

char *typeName[6] = {"Id", "Int", "Keyword", "Literal", "Char", "None"};

char *p; // 目前掃描到的位置
char *token;
int  type = None;
char code[1000000];

#define SYM_SIZE 1000*100

Pair symList[SYM_SIZE] = {
  {"puts", puts}
};

char strTableText[100000];
StrTable strTable;

#define isDigit(ch) ((ch) >= '0' && (ch) <='9')

#define isAlpha(ch) (((ch) >= 'a' && (ch) <='z') || ((ch) >= 'A' && (ch) <= 'Z'))

int E();

int readText(char *fileName, char *text, int size) {
  FILE *file = fopen(fileName, "r");
  int len = fread(text, 1, size, file);
  text[len] = '\0';
  fclose(file);
  return len;
}

void symAdd(Map *map, char *label, int address) {
  addr[map->top] = address;
  Pair p = c6mapAdd(map, c6strNew(&strTable, label), &addr[map->top]);
  printf("  p.key=%s *p.value=%d top=%d\n", p.key, *(int*)p.value, map->top);
}

char *next() {
  char *start = p;
  if (*p == '\0') return NULL;
  if (*p == '"') {
    p++;
    while (*p != '"') p++;
    p++;
    nextType = Literal;
  } else if (*p >='0' && *p <='9') { // 數字
    while (*p >='0' && *p <='9') p++;
    nextType = Int;
  } else if (isAlpha(*p) || *p == '_') { // 變數名稱或關鍵字
    while (isAlpha(*p) || isDigit(*p) || *p == '_') p++;
    nextType = Id;
  } else { // 單一字元
    p++;
    nextType = Char;
  }

  int len = p-start;
  strncpy(nextToken, start, len);
  nextToken[len] = '\0';
  return token;
}

int lex(char *code) {
  p = code;
  while (next() != NULL) {
    printf("%-10s %-10s\n", typeName[type], token);
  }
}

int isNext(char *set) {
  char member[100];
  sprintf(member, " %s ", nextToken);
  return (*token != '\0' && strstr(set, member) != NULL);
}

int tempIdx = 0;

#define nextTemp() (tempIdx++)

// F = Number | Id | '(' E ')'
int F() {
  int f;
  if (isNext(" ( ")) { // '(' E ')'
    next();
    f = E();
    next();
  } else { // Number | Id
    f = nextTemp();
    char *item = next();
    printf("t%d=%c\n", f, item);
  }
  return f; 
}

// T = F ([*/] F)*
int T() {
  int f1 = F();
  while (isNext(" * / ")) {
    char *op = next();
    int f2 = F();
    int f = nextTemp();
    printf("t%d=t%d%ct%d\n", f, f1, op, f2);
    f1 = f;
  }
  return f1;
}

int E() {
  int i1 = T();
  while (isNext(" + - ")) {
    char *op = next();
    int i2 = T();
    int i = nextTemp();
    printf("t%d=t%d%ct%d\n", i, i1, op, i2);
    i1 = i;
  }
  return i1;
}

void parse(char *code) {
  p = code;
  E();
}

int main(int argc, char * argv[]) {
  c6mapNew(&symTab, symList, SYM_SIZE);
  c6strTable(&strTable, strTableText, c6size(strTableText));
  readText(argv[1], code, sizeof(code));
  puts(code);
  lex(code);
  parse(code);
}
