#include "Parser.h"

Parser *parse(char *text) {        // 剖析器的主要函數          
  Parser *p=ParserNew();           // 建立剖析器       
  ParserParse(p, text);            // 開始剖析         
  return p;                        // 傳回剖析器       
}

char* nextToken(Parser *p);
char *tokenToType(char *token);
Tree* push(Parser *p, char* term);
Tree* pop(Parser *p, char* term);
Tree* parseProg(Parser *p);
void parseBlock(Parser *p);
void parseFor(Parser *p);
void parseBaseList(Parser *p);
void parseBase(Parser *p);
void parseStmt(Parser *p);
void parseExp(Parser *p);
void parseCond(Parser *p);
void error();
BOOL isEnd(Parser *p);
BOOL isNext(Parser *p, char *pTypes);
char *next(Parser *p, char *pTypes);

Parser *ParserNew() {
  Parser *parser = ObjNew(Parser, 1);
  parser->tokens = NULL;
  parser->tree = NULL;
  parser->stack = ArrayNew(10);
  return parser;
}

void ParserFree(Parser *parser) {
  ArrayFree(parser->tokens, strFree);
  ArrayFree(parser->stack, NULL);
  TreeFree(parser->tree);
  ObjFree(parser);
}

void ParserParse(Parser *p, char *text) {                 // 剖析物件的主函數            
  printf("======= tokenize =======\n");                   //   首先呼叫掃描器的主函數 tokenize() 將程式轉換為詞彙串列
  p->tokens = tokenize(text);                             
  printTokens(p->tokens);                                                     
  p->tokenIdx = 0;                                                                    
  printf("======= parsing ========\n");                                       
  p->tree = parseProg(p);                                 // 開始剖析 PROG = BaseList
  if (p->stack->count != 0) {                             // 如果剖析完成後堆疊是空的，那就是剖析成功 
    printf("parse fail:stack.count=%d", p->stack->count); //   否則就提示錯誤訊息
    error();                                                               
  }
}

void error() {
  printf("error()!\n");
  exit(1);
}

// PROG = BaseList
Tree *parseProg(Parser *p) {                // 剖析 PROG=BaseList 規則    
  push(p, "PROG");                                                      
  parseBaseList(p);                         // 建立 PROG 的樹根          
  return pop(p, "PROG");                    //  剖析 BaseList，            
}                                           // 取出 PROG 的剖析樹        
                                                                        
// BaseList= (BASE)*                        // 剖析 BaseList =(BASE)* 規則  
void parseBaseList(Parser *p) {                                         
  push(p, "BaseList");                      // 建立 BaseList 的樹根      
  while (!isEnd(p) && !isNext(p, "}"))      //  剖析 BASE，直到程式結束或碰到 } 為止
      parseBase(p);                                        
  pop(p, "BaseList");                       // 取出 BaseList 的剖析樹    
}

// BASE = FOR | STMT ';'
void parseBase(Parser *p) {                 // 剖析 BASE = FOR|STMT 規則                           
  push(p, "BASE");                                                                                
  if (isNext(p, "for"))                     // 建立 BASE 的樹根                                     
      parseFor(p);                          // 如果下一個詞彙是 for                                  
  else {                                    //  根據 FOR 規則進行剖析                                
      parseStmt(p);                         // 否則                                                  
      next(p, ";");                         //  根據 STMT 規則進行剖析                               
  }                                                                                               
  pop(p, "BASE");                           // 取出 BASE 的剖析樹                                  
}                                                                                                 
                                                                                                  
// FOR = for (STMT; COND; STMT) BLOCK       // 剖析 FOR = for ( STMT ; COND ; STMT ) BLOCK 
void parseFor(Parser *p) {                  // 建立 FOR 的樹根                                     
  push(p, "FOR");                           // 取得 for                                             
  next(p, "for");                           // 取得 (                                               
  next(p, "(");                             // 剖析 STMT                                          
  parseStmt(p);                             // 取得 ;                                               
  next(p, ";");                             // 剖析 COND                                          
  parseCond(p);                             // 取得 ;                                               
  next(p, ";");                             // 剖析 STMT                                          
  parseStmt(p);                             // 取得 )                                               
  next(p, ")");                             // 剖析 BLOCK                                         
  parseBlock(p);                            // 取出 FOR 的剖析樹                                   
  pop(p, "FOR");
}

// BLOCK = '{' BaseList '}'
void parseBlock(Parser *p) {
  push(p, "BLOCK");
  next(p, "{");
  parseBaseList(p);
  next(p, "}");
  pop(p, "BLOCK");
}

// STMT = return id | id '=' EXP  | id OP1
void parseStmt(Parser *p) {
  push(p, "STMT");
  if (isNext(p, "return")) {
    next(p, "return");
    next(p, "id");
  } else {
    next(p, "id");
    if (isNext(p, "="))  { // id '=' EXP   --> ASSIGN
      next(p, "=");
      parseExp(p);
    } else              // id OP1
      next(p, OP1);
  }
  pop(p, "STMT");
}

// EXP = ITEM [+-*/] ITEM | ITEM
void parseExp(Parser *p) {
  push(p, "EXP");
  next(p, ITEM);
  if (isNext(p, OP2)) {
      next(p, OP2);
      next(p, ITEM);
  }
  pop(p, "EXP");
}

// COND = EXP COND_OP EXP
void parseCond(Parser *p) {
  push(p, "COND");
  parseExp(p);
  next(p, COND_OP);
  parseExp(p);
  pop(p, "COND");
}

char* level(Parser *p) {
  return strSpaces(p->stack->count);
}

char* nextToken(Parser *p) {
  return (char*) p->tokens->item[p->tokenIdx];
}

BOOL isEnd(Parser *p) {
  return (p->tokenIdx >= p->tokens->count);
}

BOOL isNext(Parser *p, char *pTypes) {
  char *token = nextToken(p); 
  if (token == NULL) return FALSE;
  char *type = tokenToType(token);
  char tTypes[MAX_LEN+1];
  sprintf(tTypes, "|%s|", pTypes);
  if (strPartOf(type, tTypes))
    return TRUE;
  else
    return FALSE;
}
        
char *next(Parser *p, char *pTypes) {                         // 檢查下一個詞彙的型態                                          
  char *token = nextToken(p);                                 // 取得下一個詞彙                                               
  if (isNext(p, pTypes)) {                                    // 如果是pTypes型態之一                                         
    char *type = tokenToType(token);                          //   取得型態                                                    
    Tree *child = TreeNew(type, token);                       //   建立詞彙節點(token,type)                                    
    Tree *parentTree = ArrayPeek(p->stack);                   //   取得父節點，                                                
    TreeAddChild(parentTree, child);                          //   加入父節點成為子樹                                          
    printf("%s idx=%d, token=%s, type=%s\n",                  //   印出詞彙以便觀察                                            
      level(p),p->tokenIdx,token,type);                                                                                     
    p->tokenIdx++;                                            //   前進到下一個節點                                            
    return token;                                             //   傳回該詞彙                                                  
  } else {                                                    // 否則(下一個節點型態錯誤)                                     
    printf("next():%s is not type(%s)\n", token, pTypes);     //   印出錯誤訊息                                                
    error();                                                                                                                
    p->tokenIdx++;                                            //  前進到下一個節點                                                                                                          
    return NULL;                                              
  }                                                                                                                         
}                                                                                                                           
                                                                                                                            
Tree* push(Parser *p, char* pType) {                          // 建立 pType 型態的子樹，推入堆疊中                                                              
  printf("%s+%s\n", level(p), pType);                                                      
  Tree* tree = TreeNew(pType, "");                                                                                          
  ArrayPush(p->stack, tree);                                                                                                
  return tree;                                                                                                              
}                                                                                                                           
                                                                                                                            
Tree* pop(Parser *p, char* pType) {                           // 取出 pType型態的子樹                                          
  Tree *tree = ArrayPop(p->stack);                            // 取得堆疊最上層的子樹                                         
  printf("%s-%s\n", level(p), tree->type);                    // 印出以便觀察                                                 
  if (strcmp(tree->type, pType)!=0) {                         // 如果型態不符合                                               
    printf("pop(%s):should be %s\n",tree->type,pType);        //  印出錯誤訊息                                                
	error();                                                                                                                   
  }                                                                                                                         
  if (p->stack->count > 0) {                                  // 如果堆疊不是空的                                                                       
    Tree *parentTree = ArrayPeek(p->stack);                   //  取出上一層剖析樹                                             
    TreeAddChild(parentTree, tree);                           //  將建構完成的剖析樹加入上一層節點中，成為子樹
  }
  return tree;                                                                                     
}                                                                                                                           
                                                                                                                            
                                                                                                                            
