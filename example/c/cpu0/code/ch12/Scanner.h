#ifndef SCANNER_H
#define SCANNER_H

#include "Array.h"

typedef struct {        // 掃描器的物件結構              
  char *text;           //   輸入的程式 (text) 
  int textLen;          //   目前掃描到的位置  
  int textIdx;          //   程式的總長度      
  char token[MAX_LEN];  //   目前掃描到的詞彙  
} Scanner;

Scanner* ScannerNew(char *pText);
void ScannerFree(Scanner *scanner);
char* ScannerScan(Scanner *scanner);
Array* tokenize(char *text);
char *tokenToType(char *token);
void printTokens(Array *tokens);

extern char STRING[];
extern char NUMBER[];
extern char ID[];
extern char KEYWORDS[];
extern char OP1[];
extern char OP2[];
extern char COND_OP[];
extern char ITEM[];

#endif
