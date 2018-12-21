#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "Cpu0.h"

typedef struct {                                    // 組譯器物件                     
  Array *codes;                                     //   指令物件串列                 
  HashTable *symTable;                              //   符號表                       
  HashTable *opTable;                               //   指令表                       
} Assembler;                                                                       
                                                                                   
typedef struct {                                    // 指令物件                       
  int address, opCode, size;                        //   包含位址、運算碼、           
  char *label, *op, *args, type;                    //   空間大小、op, 、標記、       
  char *objCode;                                    //   參數、型態、目的碼           
} AsmCode;                                          //   等欄位                       
                                                                                   
void assemble(char *asmFile, char *objFile);        // 組譯器的主程式              
                                                                                   
Assembler* AsmNew();                                // 組譯器的建構函數               
void AsmFree(Assembler *a);                         // 組譯器的解構函數               
                                                                                   
void AsmPass1(Assembler *a, char *text);            // 組譯器的第一階段               
void AsmPass2(Assembler *a);                        // 組譯器的第二階段               
void AsmSaveObjFile(Assembler *a, char *objFile);   // 儲存目的檔                     
void AsmTranslateCode(Assembler *a, AsmCode *code); // 將指令轉為目的碼               
                                                                                   
AsmCode* AsmCodeNew(char *line);                                                   
void AsmCodeFree(AsmCode *code);                    // 指令物件的建構函數             
int AsmCodePrintln(AsmCode *code);                  // 指令物件的解構函數             
                                                    // 指令物件的列印函數             
#endif



























