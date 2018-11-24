#include <string.h>
#include "Scanner.h"

char STRING[] = "string";
char NUMBER[] = "number";
char ID[]  = "id";
char KEYWORDS[] = "|if|for|while|return|";
char OP1[] = "|++|--|";
char OP2[] = "|+|-|*|/|";
char COND_OP[] = "|==|!=|<=|>=|<|>|";
char ITEM[]= "|id|number|string|";
char OP[]  = "+-*/<=>!";

#define ch() (scanner->text[scanner->textIdx])
#define next() (scanner->textIdx++)

Scanner* ScannerNew(char *pText) {
  Scanner *scanner = ObjNew(Scanner, 1);
  scanner->text = pText;
  scanner->textLen = strlen(pText);
  scanner->textIdx = 0;
  return scanner;
}

void ScannerFree(Scanner *scanner) {
  ObjFree(scanner);
}

char *ScannerScan(Scanner *scanner) {                                           // 掃描下一個詞彙                           
  while (strMember(ch(), SPACE))                                                // 忽略空白                                 
    next();                                                                                                              
  if (scanner->textIdx >= scanner->textLen)                                     // 檢查是否超過範圍                         
    return NULL;                                                                                                         
  char c = ch();                                                                // 取得下一個字元                           
  int begin = scanner->textIdx;                                                 // 記住詞彙開始點                           
  if (c == '\"') { // string = ".."                                             // 如果是 "，代表字串開頭，                 
    next(); // skip begin quote "                                                 
    while (ch() != '\"') next();                                                // 一直讀到下一個 " 符號為止。                                 
    next(); // skip end quote "                                                                                          
  } else if (strMember(c, OP)) { // OP , ex : ++, --, <=, >=, ...               // 如果是OP(+-*/<=>!等符號)                 
    while (strMember(ch(), OP)) next();                                         // 一直讀到不是OP為止                     
  } else if (strMember(c, DIGIT)) { // number, ex : 312, 77568, ...             // 如果是數字                               
    while (strMember(ch(), DIGIT)) next();                                      // 一直讀到不是數字為止                   
  } else if (strMember(c, ALPHA)) { // name, ex : int, sum, i, for, if, ....    // 如果是英文字母                           
    while (strMember(ch(), ALPHA) || strMember(ch(), DIGIT)) next();            // 一直讀到不是英文字母 (或數字)為止 (ex: x1y2z)
  } else // some other symbol, such as #                                                         
    next();                                                                     // 否則，傳回單一字元                                                                
  strSubstr(scanner->token, scanner->text, begin, scanner->textIdx-begin);      // 設定token為(begin…textIdx) 之間的子字串
  return scanner->token;                                                        // 傳回token詞彙
}                                                                                             
                                                                                                             
Array* tokenize(char *text) {                                                   // 將程式轉換成一個一個的詞彙                             
  Array *tokens = ArrayNew(10);                                                                                                                     
  Scanner *scanner = ScannerNew(text);                                                                                                              
  char *token = NULL;                                                                                                    
  while ((token = ScannerScan(scanner))!= NULL) {                               // 不斷取出下一個詞彙，直到程式字串結束為止
    ArrayAdd(tokens, newStr(token));                                            
    printf("token=%s\n", token);                                                              
  }                                                                                           
  ScannerFree(scanner);                                                                       
  return tokens;                                                                                                         
}                                                                                                                        
                                                                                                                         
char *tokenToType(char *token) {                                                // 判斷並取得 token的型態                                                
  if (strPartOf(token, KEYWORDS))                                               //   如果是關鍵字 if, for, …                                            
    return token;                                                               //   型態即為該關鍵字                                                  
  else if (token[0] == '\"')                                                    // 如果以符號 " 開頭，則                  
    return STRING;                                                              //   型態為 STRING                        
  else if (strMember(token[0], DIGIT))                                          // 如果是數字開頭，則                     
    return NUMBER;                                                              //   型態為 NUMBER                        
  else if (strMember(token[0], ALPHA))                                          // 如果是英文字母開頭，則                 
    return ID;                                                                  //   型態為 ID                            
  else                                                                          // 否則 (像是 +,-,*,/,>,<,….)            
    return token;                                                               //   型態即為該 token                     
}                                                                                           
                                                                                            
void printTokens(Array *tokens) {                                                           
  printf("tokens->count = %d\n", tokens->count);
  int i;
  for (i=0; i<tokens->count; i++) {
    char *token = tokens->item[i];
    printf("token=%s , type=%s\n", token, tokenToType(token));
  }
}
