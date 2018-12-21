#include "../lib/compiler.h"

// FUNC = function id (idLIST) BLOCK
void FUNC() {
  skip("function");
  char *id = skipType(Id);
  vmCode("function", id, "", "");
  skip("(");
  if (!isNext(")")) {
    char *p = skipType(Id);
    vmCode(Param, p, "", "");
    while (isNext(",")) {
      skip(",");
      p = skipType(Id);
      vmCode(Param, p, "", "");
    }
  }
  skip(")");
  BLOCK(Local);
  vmCode("fend", id, "", "");
}

// PROG = FUNCTION | STMT // VAR; | 
void PROG() {
  next();
  while (!isEnd()) {
    if (isNext("function"))
      FUNC();
    /*
    else if (isNext("var")) {
      VAR(Global);
      skip(";");
    } */
    else
      STMT();
  }
}

int main(int argc, char * argv[]) {
  compileFile(argv[1], "j0");
}