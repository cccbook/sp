#include <stdio.h>
#include <string.h>

int E();

enum { Id, Int, Keyword, Literal, Char };

char *typeName[5] = {"Id", "Int", "Keyword", "Literal", "Char"};

char *p; // 目前掃描到的位置
char token[100], lastToken[100];
int  type, lastType;
char code[1000000];

#define isDigit(ch) ((ch) >= '0' && (ch) <='9')

#define isAlpha(ch) (((ch) >= 'a' && (ch) <='z') || ((ch) >= 'A' && (ch) <= 'Z'))

int tempIdx = 0;

#define nextTemp() (tempIdx++)

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
  // printf("token=%s\n", token);
  return token;
}

int lex(char *fileName) {
  p = code;
  while (1) {
    if (next() == NULL) break;
    printf("%-10s %-10s\n", typeName[type], token);
  }
}

int cNext(char *set) {
  return (strchr(set, *p) != NULL);
}

// F = (E) | Number | Id
int F() {
  int f;
  if (cNext("(")) { // '(' E ')'
    next(); // (
    f = E();
    next(); // )
  } else { // Number | Id
    f = nextTemp();
    char *item = next();
    printf("t%d=%s\n", f, item);
  }
  return f;
}

// E = F (op E)*
int E() {
  int i1 = F();
  while (cNext("+-*/")) {
    char op = *p;
    next();
    int i2 = E();
    int i = nextTemp();
    printf("t%d=t%d%ct%d\n", i, i1, op, i2);
    i1 = i;
  }
  return i1;
}

// STMT = id '=' E;

int STMT() {
  char id[100];
  next();
  strcpy(id, token);
  if (cNext("=")) next();
  int e = E();
  if (cNext(";")) next();
  printf("%s=t%d\n", id, e);
}

// while (E) STMT
int WHILE() {
  
}

/*
// id = E
void assign() {
  char id[100];
  next();
  strcpy(id, token); 
  next(); // =
  E();
}
*/

void prog() {
  STMT();
}

void parse(char *code) {
  p = code;
  prog();
}

int main(int argc, char * argv[]) {
  readText(argv[1], code, sizeof(code));
  puts(code);
  // lex(code);
  parse(code);
}

