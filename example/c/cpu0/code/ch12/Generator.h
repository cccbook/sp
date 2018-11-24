#ifndef GENERATOR_H
#define GENERATOR_H

#include "Tree.h"
#include "HashTable.h"

typedef struct {                                                                          // 程式碼產生器物件                
  HashTable *symTable;                                                                    //   符號表                        
  Tree *tree;                                                                             //   剖析樹                        
  FILE *asmFile;                                                                          //   輸出的CPU0組合語言檔          
  int forCount, varCount;                                                                 //   For迴圈與臨時變數的數量       
} Generator;                                                                                                              
                                                                                                                          
void generate(Tree *tree, char *asmFile);                                                 // 程式碼產生器的主函數            
                                                                                                                          
Generator *GenNew();                                                                      // Generator 的建構函數            
void GenFree(Generator *g);                                                               // Generator 的解構函數            
Tree* GenCode(Generator *g, Tree *node, char *rzVar);                                     // 產生組合語言程式碼              
void GenData(Generator *g);                                                               // 產生資料宣告                    
void GenPcode(Generator *g, char* label, char* op, char* p1, char* p2, char* pTo);        // 輸出虛擬碼 pcode                
void GenPcodeToAsm(Generator *g, char* label, char* op, char* p1, char* p2, char* pTo);   // 將虛擬碼轉為組合語言            
void GenAsmCode(Generator *g, char* label, char* op, char* p1, char* p2, char* pTo);      // 輸出組合語言指令                
void GenTempVar(Generator *g, char *tempVar);                                             // 取得下一個臨時變數名稱          
void negateOp(char *condOp, char *negOp);                                                 // 取比較運算的互補運算,ex: < 變 >=

#endif


















