#ifndef PARSER_H
#define PARSER_H

#include "Scanner.h"
#include "Tree.h"

typedef struct {                           // 剖析器的物件結構      
  Array *tokens;                           //   詞彙串列         
  Tree *tree;                              //   剖析樹 (樹根)    
  Array* stack;                            //   剖析過程用的堆疊 
  int tokenIdx;                            //   詞彙指標         
} Parser;                                                     
                                                              
Parser *parse(char *text);                 // 剖析器的主程式     
                                                              
Parser *ParserNew();                       // 剖析器的建構函數   
void ParserParse(Parser *p, char *text);   // 剖析器的剖析函數   
void ParserFree(Parser *parser);           // 釋放記憶體         

#endif












       
