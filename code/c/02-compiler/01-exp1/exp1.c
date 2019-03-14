#include <stdio.h>
#include <assert.h>
#include <string.h>

int tokenIdx = 0;
char *tokens;

int E();

char ch() {
  char c = tokens[tokenIdx];
  return c;
}

char next() {
  char c = ch();
  tokenIdx++;
  return c;
}

int isNext(char *set) {
  return (ch()!='\0' && strchr(set, ch())!=NULL);
}

int nextTemp() {
  static int tempIdx = 0;
  return tempIdx++;
}

// F = Number | Id | '(' E ')'
int F() {
  int f;
  if (ch()=='(') { // '(' E ')'
    next();
    f = E();
    assert(ch()==')');
    next();
  } else { // Number | Id
    f = nextTemp();
    char c=next();
    printf("t%d=%c\n", f, c);
  }
  return f; 
}

// T = F ([*/] F)*
int T() {
  int f1 = F();
  while (isNext("*/")) {
    char op=next();
    int f2 = F();
    int f = nextTemp();
    printf("t%d=t%d%ct%d\n", f, f1, op, f2);
    f1 = f;
  }
  return f1;
}

// E = T ([+-] T)*
int E() {
  int i1 = T();
  while (isNext("+-")) {
    char op=next();
    int i2 = T();
    int i = nextTemp();
    printf("t%d=t%d%ct%d\n", i, i1, op, i2);
    i1 = i;
  }
  return i1;
}

void parse(char *str) {
  tokens = str;
  E();
}

int main(int argc, char * argv[]) {
  printf("=== EBNF Grammar =====\n");
  printf("E=T ([+-] T)*\n");
  printf("T=F ([*/] F)*\n");
  printf("F=Number | Id | '(' E ')'\n");
  printf("==== parse:%s ========\n", argv[1]);
  parse(argv[1]);
}