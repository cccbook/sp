#include "compiler.h"

void PARAM() {
  char *type = skipType(Type);
  char *star = "";
  if (isNext("*")) star = skip("*");
  char *id = skipType(Id);
  vmCode("param", id, typeStar(type, star), "");
}

// PROG = (INCLUDE | DECL | FUNCTION)*
// INCLUDE  = #...>
// FUNCTION = type id (PARAM_LIST) BLOCK
// DECL     = type id (, id)* ;
void PROG() {
  next();
  while (!isEnd()) {
    if (isNext("#")) { // INCLUDE
      while (!isNext(">")) next();
      skip(">");
      continue;
    }
    char *type = skipType(Type);
    char *star = "";
    if (isNext("*")) star = skip("*");
    char *id = skipType(Id);
    if (isNext("(")) { // FUNCTION = type id (PARAM_LIST) BLOCK
      vmCode("function", id, typeStar(type, star), "");
      skip("(");
      if (!isNext(")")) {
        PARAM();
        while (!isNext(")")) {
          skip(",");
          PARAM();
        }
      }
      skip(")");
      BLOCK(Local);
      vmCode("-function", id, "", "");
    } else { // DECL = type *? id (, *? id)* ;
      vmGlobal("global", id, typeStar(type, star), "");
      while (isNext(",")) {
        skip(",");
        star = "";
        if (isNext("*")) star = skip("*");
        id = skipType(Id);
        vmGlobal("global", id, typeStar(type, star), "");
      }
      skip(";");
    }
  }
}

int main(int argc, char * argv[]) {
  compileFile(argv[1], "c");
}