#include "Parser.h"
#include "Generator.h"

void compile(char *cFile, char *asmFile) {     // 編譯器主程式                  
  printf("compile file:%s\n", cFile, asmFile);                               
  char *cText = newFileStr(cFile);             //   讀取檔案到 cText 字串中。   
  Parser *parser = parse(cText);               //   剖析程式 (cText) 轉為語法樹 
  generate(parser->tree, asmFile);             //   程式碼產生                  
  ParserFree(parser);                          //   釋放記憶體                  
  freeMemory(cText);
}





   
