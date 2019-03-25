#include <assert.h>
#include "compiler.h"

int  E();
void STMT();
void IF();
void BLOCK();

int tempIdx = 1, labelIdx = 1;

#define nextTemp() (tempIdx++)
#define nextLabel() (labelIdx++)

int isNext(char *set) {
  char eset[SMAX], etoken[SMAX];
  sprintf(eset, " %s ", set);
  sprintf(etoken, " %s ", tokens[tokenIdx]);
  return (tokenIdx < tokenTop && strstr(eset, etoken) != NULL);
}

int isNextType(TokenType type) {
  return (types[tokenIdx] == type);
}

int isEnd() {
  return tokenIdx >= tokenTop;
}

char *next() {
  // printf("%02d:token = %-10s type = %-10s\n", tokenIdx, tokens[tokenIdx], typeName[types[tokenIdx]]);
  return tokens[tokenIdx++];
}

char *skip(char *set) {
  if (isNext(set)) {
    return next();
  } else {
    error("skip(%s) got %s fail!\n", set, next());
  }
}

char *skipType(TokenType type) {
  if (isNextType(type)) {
    return next();
  } else {
    error("skipType(%s) got %s fail!\n", typeName[type], typeName[types[tokenIdx]]);
  }
}

// CALL(id) = (E*)
int CALL(char *id) {
  assert(isNext("("));
  skip("(");
  int e[100], ei = 0;
  while (!isNext(")")) {
    e[ei++] = E();
    if (!isNext(")")) skip(",");
  }
  for (int i=0; i<ei; i++) {
    irEmitArg(e[i]);
  }
  skip(")");
  irEmitCall(id, ei);
  // 這裡要再加處理程式
  int r = nextTemp();
  return r;
}

// F = (E) | Number | Id | CALL
int F() {
  int f;
  if (isNext("(")) { // '(' E ')'
    next(); // (
    f = E();
    next(); // )
  } else { // Number | Id | CALL
    f = nextTemp();
    char *item = next();
    irEmitAssignTs(f, item);
  }
  return f;
}

// E = F (op E)*
int E() {
  int i1 = F();
  while (isNext("+ - * / & | < > = <= >= == != && ||")) {
    char *op = next();
    int i2 = E();
    int i = nextTemp();
    irEmitOp2(i, i1, op, i2);
    i1 = i;
  }
  return i1;
}

// EXP = E
int EXP() {
  tempIdx = 1; // 讓 temp 重新開始，才不會 temp 太多！
  return E();
}

// ASSIGN(id) = '=' E
void ASSIGN(char *id) {
  skip("=");
  int e = EXP();
  irEmitAssignSt(id, e);
}

// while (E) STMT
void WHILE() {
  int whileBegin = nextLabel();
  int whileEnd = nextLabel();
  irEmitLabel(whileBegin);
  skip("while");
  skip("(");
  int e = E();
  irEmitIfNotGoto(e, whileEnd);
  skip(")");
  STMT();
  irEmitGoto(whileBegin);
  irEmitLabel(whileEnd);
}

// STMT = WHILE | BLOCK | CALL ; | ASSIGN ;
void STMT() {
  if (isNext("while"))
    WHILE();
  // else if (isNext("if"))
  //   IF();
  else if (isNext("{"))
    BLOCK();
  else {
    char *id = next();
    /*
    if (eq(id, "int")) {
      skip("int");
      while (!isNext(";")) {
        char *var = skipType(Id);
        mapAdd(symMap, var, &symList[symTop++]);
      }
    }
    */
    if (isNext("(")) {
      CALL(id);
    } else {
      ASSIGN(id);
    }
    skip(";");
  }
}

// STMTS = STMT*
void STMTS() {
  while (!isEnd() && !isNext("}")) {
    STMT();
  }
}

// BLOCK = { STMT* }
void BLOCK() {
  skip("{");
  STMTS();
  skip("}");
}

// PROG = STMT*
void PROG() {
  STMTS();
}

void parse() {
  debug("============ parse =============\n");
  tokenIdx = 0;
  PROG();
}
