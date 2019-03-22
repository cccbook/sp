#include <assert.h>
#include "compiler.h"

int E();
void STMT();
void IF();
void BLOCK();

int tempIdx = 1, labelIdx = 1;

#define nextTemp() (tempIdx++)
#define nextLabel() (labelIdx++)
// #define emit printf

int isNext(char *set) {
  char eset[SMAX], etoken[SMAX];
  sprintf(eset, " %s ", set);
  sprintf(etoken, " %s ", tokens[tokenIdx]);
  return (tokenIdx < tokenTop && strstr(eset, etoken) != NULL);
}

int isEnd() {
  return tokenIdx >= tokenTop;
}

char *next() {
  // printf("token[%d]=%s\n", tokenIdx, tokens[tokenIdx]);
  return tokens[tokenIdx++];
}

char *skip(char *set) {
  if (isNext(set)) {
    return next();
  } else {
    printf("skip(%s) got %s fail!\n", set, next());
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
    irEmitTs(f, item);
    // emit("t%d = %s\n", f, item);
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
    irEmitOp2(i, i1, op, i2);
    // emit("t%d = t%d %s t%d\n", i, i1, op, i2);
    i1 = i;
  }
  return i1;
}

// ASSIGN = id '=' E;
void ASSIGN() {
  char *id = next();
  skip("=");
  int e = E();
  skip(";");
  irEmitSt(id, e);
  // emit("%s = t%d\n", id, e);
}

// while (E) STMT
void WHILE() {
  int whileBegin = nextLabel();
  int whileEnd = nextLabel();
  irEmitLabel(whileBegin);
  // emit("(L%d)\n", whileBegin);
  skip("while");
  skip("(");
  int e = E();
  irEmitIfGoto(e, whileBegin);
  // emit("goif T%d L%d\n", whileEnd, e);
  skip(")");
  STMT();
  irEmitGoto(whileBegin);
  // emit("goto L%d\n", whileBegin);
  irEmitLabel(whileEnd);
  // emit("(L%d)\n", whileEnd);
}

void STMT() {
  if (isNext("while"))
    return WHILE();
  // else if (isNext("if"))
  //   IF();
  else if (isNext("{"))
    BLOCK();
  else
    ASSIGN();
}

void STMTS() {
  while (!isEnd() && !isNext("}")) {
    STMT();
  }
}

// { STMT* }
void BLOCK() {
  skip("{");
  STMTS();
  skip("}");
}

void PROG() {
  STMTS();
}

void parse() {
  printf("============ parse =============\n");
  tokenIdx = 0;
  PROG();
}
