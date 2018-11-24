#include <assert.h>
#include "compiler.h"

int E();

int tempIdx = 0, labelIdx = 0;

#define nextTemp() (tempIdx++)
#define nextLabel() (labelIdx++)
#define genCode printf

int isNext(char *set) {
  char eset[SMAX], etoken[SMAX];
  sprintf(eset, " %s ", set);
  sprintf(etoken, " %s ", tokens[tokenIdx]);
  return (tokenIdx < tokenTop && strstr(eset, etoken) != NULL);
}

char *next() {
  return tokens[tokenIdx++];
}

char *skip(char *set) {
  if (isNext(set)) {
    return next();
  } else {
    printf("skip(%s) fail!", set);
    assert(0);
  }
}

// F = (E) | Number | Id
int F() {
  int f;
  if (isNext("(")) { // '(' E ')'
    next(); // (
    f = E();
    next(); // )
  } else { // Number | Id
    f = nextTemp();
    char *item = next();
    genCode("t%d = %s\n", f, item);
  }
  return f;
}

// E = F (op E)*
int E() {
  int i1 = F();
  while (isNext("+ - * / & | ! < > =")) {
    char *op = next();
    int i2 = E();
    int i = nextTemp();
    genCode("t%d = t%d %s t%d\n", i, i1, op, i2);
    i1 = i;
  }
  return i1;
}

// STMT = id '=' E;
int STMT() {
  char *id = next();
  skip("=");
  int e = E();
  skip(";");
  genCode("%s = t%d\n", id, e);
}

// while (E) STMT
int WHILE() {
  int whileBegin = nextLabel();
  int whileEnd = nextLabel();
  genCode("(L%d)\n", whileBegin);
  skip("while");
  skip("(");
  int e = E();
  genCode("goto L%d if T%d\n", whileEnd, e);
  skip(")");
  STMT();
  genCode("goto L%d\n", whileBegin);
  genCode("(L%d)\n", whileEnd);
}

void prog() {
  // STMT();
  WHILE();
}

void parse() {
  printf("============ parse =============\n");
  tokenIdx = 0;
  prog();
}