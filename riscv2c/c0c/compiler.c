#include "compiler.h"

FILE *pFile, *sFile; 
char code[TMAX];

char *typeStar(char *type, char *star) {
  return stPrint("%s%s", type, star);
}

// P = ((E) | Number | Literal | ID) ([E] | (LIST<E>) | ++ | --)
char *P() {
  char *p;
  if (isNext("(")) { // '(' E ')'
    skip("("); // (
    p = E();
    skip(")"); // )
  } else if (isNextType(Literal)) { // ex: Literal : "hello ...."
    char *str = next();
    p = vmNextLabel("Str");
    vmGlobal("str", p, str, "");
  } else if (isNextType(Number)) { // ex: Number: 347
    p = next();
  } else if (isNextType(Id)) {
    p = next();
  }
  while (isNext("[ ( ++ --")) {
    if (isNext("[")) {
      skip("[");
      char *e = E();
      skip("]");
      char *t = vmNextTemp();
      vmCode("[]", t, p, e);
      p = t;
    } else if (isNext("(")) {
      p = CALL(p);
    } else if (isNext("++ --")) {
      char *op = next();
      vmCode(op, p, "", "");
    }
  }
  return p;
}

// F = (++ | -- | [*&+-~!])? P
char *F() {
  char *op0 = NULL;
  if (isNext("* & + - ~ ! ++ --")) op0 = next();
  char *f = P();
  if (op0 != NULL) {
    char *t = vmNextTemp();
    vmCode(op0, t, f, "");
    f = t;
  }
  return f;
}

// E = F (op F)*
char *E() {
  char *f = F();
  while (isNext("+ - * / & | && || < > <= >= != ==")) {
    char *op = next();
    char *f2 = F();
    char *t = vmNextTemp();
    vmCode(op, t, f, f2);
    f = t;
  }
  return f;
}

// EXP = E
char *EXP() {
  tempIdx = 0; // 每個運算式 E 都會從 t0 開始設立臨時變數，這樣才能知道每個函數到底需要多少個臨時變數。
  char *e = E();
  return e;
}

// while (E) STMT
void WHILE() {
  char *whileBegin = vmNextLabel("WBEGIN");
  char *whileEnd = vmNextLabel("WEND");
  vmLabel(whileBegin);
  skip("while");
  skip("(");
  char *e = EXP();
  vmCode("jz", whileEnd, e, "");
  skip(")");
  STMT();
  vmCode("jmp", whileBegin, "", "");
  vmLabel(whileEnd);
}

// if (E) STMT (else STMT)?
void IF() {
  char *elseBegin = vmNextLabel("ELSE");
  char *ifEnd = vmNextLabel("ENDIF");
  skip("if");
  skip("(");
  char *e = EXP();
  vmCode("jz", elseBegin, e, "");
  skip(")");
  STMT();
  vmCode("jmp", ifEnd, "", "");
  vmLabel(elseBegin);
  if (isNext("else")) {
    skip("else");
    STMT();
  }
  vmLabel(ifEnd);
}

// BLOCK = { LIST<VAR> STMT* }
void BLOCK(int scope) {
  skip("{");
  while (isNextType(Type)) {
    VAR(scope);
    skip(";");
  }
  while (!isNext("}")) {
    STMT();
  }
  skip("}");
}

// return E;
void RETURN() {
  skip("return");
  char *e = EXP();
  vmCode("return", e, "", "");
  skip(";");
}

#define ARGMAX 100

// CALL(id) = id ( LIST<E> )
char *CALL(char *id) {
  char *args[ARGMAX];
  int top = 0;
  skip("(");
  if (!isNext(")")) {
    args[top++] = EXP();
    while (isNext(",")) {
      skip(",");
      args[top++] = EXP();
      assert(top < ARGMAX);
    }
  }
  skip(")");
  for (int i=0; i<top; i++) {
    vmCode("arg", args[i], "", "");
  }
  char *t = vmNextTemp();
  vmCode("call", t, id, "");
  return t;
}

// ASSIGN(): P (=E)?
char *ASSIGN(int scope, char *type) {
  char *p = P();
  if (*type != '\0') vmCode("local", p, type, "");
  if (isNext("=")) {
    next();
    char *e = E();
    vmCode("=", p, e, "");
  }
  return p;
}

// DECL: *? ASSIGN
char *DECL(int scope, char *type) {
  char *star = isNext("*") ? skip("*") : "";
  return ASSIGN(scope, typeStar(type, star));
}

// STMT = WHILE | IF | BLOCK | RETURN | VAR ; | ASSIGN;
void STMT() {
  if (isNext("while"))
    WHILE();
  else if (isNext("if"))
    IF();
  else if (isNext("{"))
    BLOCK(Inner);
  else if (isNext("return"))
    RETURN();
  else if (isNextType(Type)) { // VAR ;
    VAR(Local);
    skip(";");
  } else {
    ASSIGN(Local, "");
    skip(";");
  }
}

// VAR = Type LIST<DECL>
void VAR(int scope) {
  char *type = skipType(Type);
  DECL(scope, type);
  while (isNext(",")) {
    skip(",");
    DECL(scope, type);
  }
}

void compile(char *file, char *ext, char *code) {
  char pFileName[SMAX]; 
  printf("============ compile =============\n");
  sprintf(pFileName, "%s.p0", file);
  pFile = fopen(pFileName, "wt");
  stInit();
  scanInit(code);
  vmInit();
  char *path = stPrint("\"%s.%s\"", file, ext);
  vmGlobal("file", path, "", "");
  PROG();
  vmCode("-file", path, "", "");
  // vmDump(vmGlobals, vmGlobalTop);
  // vmDump(vmCodes, vmCodeTop);
  vmToAsm(file);
  fclose(pFile);
}

void compileFile(char *file, char *ext) {
  char cFileName[SMAX]; 
  sprintf(cFileName, "%s.%s", file, ext);
  readText(cFileName, code, TMAX);
  puts(code);
  lex(code);
  compile(file, ext, code);
}
