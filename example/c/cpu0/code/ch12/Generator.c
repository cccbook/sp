#include "Generator.h"

// 程式產生器的主要函數。
void generate(Tree *tree, char *asmFile) {      // 將剖析樹 tree 轉為組合語言檔 asmFile
  char nullVar[100]="";                                                             
  Generator *g = GenNew();                      // 開啟組合語言檔以便輸出              
  g->asmFile = fopen(asmFile, "w");                                                 
  printf("=====PCODE=====\n");                  // 產生程式碼                          
  GenCode(g, tree, nullVar);                    // 產生資料宣告                        
  GenData(g);                                   // 關閉組合語言檔                      
  fclose(g->asmFile);                           // 釋放記憶體                          
  GenFree(g);                                   // 讀入組合語言檔並印出                
  char *asmText = newFileStr(asmFile);                                              
  printf("=====AsmFile:%s======\n", asmFile);                                       
  printf("%s\n", asmText);                      // 釋放記憶體                          
  freeMemory(asmText);
}

Generator *GenNew() {
  Generator *g = ObjNew(Generator, 1);
  g->symTable = HashTableNew(127);
  return g;
}

void GenFree(Generator *g) {
  HashTableFree(g->symTable);
  ObjFree(g);
}

char nullVar[100]="";

Tree* GenCode(Generator *g, Tree *node, char *rzVar) {                          // 遞迴產生節點 node 的程式碼         
  strcpy(nullVar, "");                                                                                             
  strcpy(rzVar, "");                                                                                               
  if (node == NULL) return NULL;                                                // 遞迴終止條件。                     
                                                                                                                   
  if (strEqual(node->type, "FOR")) {                                            // 處理 FOR 節點                      
    // FOR ::= 'for' '(' STMT ';' COND ';' STMT ')' BLOCK                                                
    char forBeginLabel[100], forEndLabel[100], condOp[100];                     
    Tree *stmt1 = node->childs->item[2],                                        // 取得子節點                         
         *cond  = node->childs->item[4],                                                                           
         *stmt2 = node->childs->item[6],                                                                           
         *block = node->childs->item[8];                                                                           
    GenCode(g, stmt1, nullVar);                                                 // 遞迴產生 STMT                             
    int tempForCount = g->forCount++;                                           // 設定FOR迴圈的                 
    sprintf(forBeginLabel, "FOR%d", tempForCount);                              //   進入標記                                
    sprintf(forEndLabel, "_FOR%d", tempForCount);                               //   離開標記            
    GenPcode(g, forBeginLabel, "", "", "", "");                                 // 中間碼：例如 FOR1:    
    GenCode(g, cond, condOp);                                                   // 遞迴產生 COND        
    char negOp[100];                                                                                  
    negateOp(condOp, negOp);                                                    // 互補運算negOp         
    GenPcode(g, "", "J", negOp, "", forEndLabel);                               // 中間碼：例如J > _FOR1 
    GenCode(g, block, nullVar);                                                 // 遞迴產生 BLOCK       
    GenCode(g, stmt2, nullVar);                                                 // 遞迴產生 STMT        
    GenPcode(g, "", "J", "", "", forBeginLabel);                                // 中間碼：例如J FOR1    
    GenPcode(g, forEndLabel, "", "", "", "");                                   // 中間碼：例如 _FOR1    
    return NULL;                                                                                      
  } else if (strEqual(node->type, "STMT")) {                                    // 處理 STMT 節點          
    //   STMT = return id | id '=' EXP | id ('++'|'--')                                              
    Tree *c1 = node->childs->item[0];                                           //   取得子節點              
    if (strEqual(c1->type, "return")) {                                         // 處理 return 指令                                
      Tree *id = node->childs->item[1];                                                                   
      GenPcode(g, "", "RET", "", "", id->value);                                // 中間碼： 例如 RET sum      
    } else {                                                                                              
      Tree *id = node->childs->item[0];                                         //   取得子節點              
      Tree *op = node->childs->item[1];                                                                   
      if (strEqual(op->type, "=")) {                                            // 處理 id= EXP             
        // STMT 是 id '=' EXP                                                   //  取得子節點               
        Tree *exp = node->childs->item[2];                                                                
        char expVar[100];                                                          
        GenCode(g, exp, expVar);                                                //  遞迴產生 EXP            
        GenPcode(g, "", "=", expVar, "", id->value);                            //  中間碼：例如 = 0 sum     
        HashTablePut(g->symTable, id->value, id->value);                        //  將 id 加入到符號表中                              
        strcpy(rzVar, expVar);                                                  //  傳回 EXP 的變數，例如 T0  
      } else { // STMT 是 id++ 或 id--，--> id OP1                              // 處理 id++ 或 id--         
        char addsub[100];                                                                                 
        if (strEqual(op->value, "++"))                                          //  如果是 id++              
          strcpy(addsub, "+");                                                  //   設定運算為 + 法         
        else                                                                    //  否則                     
          strcpy(addsub, "-");                                                  //   設定運算為 - 法         
        GenPcode(g, "", addsub, id->value, "1", id->value);                     //  中間碼：例如 ADD i, 1, i 
        strcpy(rzVar, id->value);                                               //  傳回id，例如 i           
      }                                                                         
    }                                                                           
  } else if (strEqual(node->type, "COND")) {                                    // 處理 COND 節點      
    // 處理判斷式 COND = EXP ('=='|'!='|'<='|'>='|'<'|'>') EXP                                
    Tree* op = node->childs->item[1];                                           // 取得子節點            
    char expVar1[100], expVar2[100];                                                                  
    GenCode(g, node->childs->item[0], expVar1);                                 //  遞迴產生 EXP       
    GenCode(g, node->childs->item[2], expVar2);                                 //  遞迴產生 EXP       
    GenPcode(g, "", "CMP", expVar1, expVar2, nullVar);                          //  中間碼：例如 CMP i,10 
    strcpy(rzVar, op->value); // 傳回布林運算子                                 //  傳回op，例如 >       
  } else if (strPartOf(node->type, "|EXP|")) {                                  // 處理 EXP
    // 處理運算式 EXP = ITEM ([+-*/] ITEM)*                                               
    Tree *item1 = node->childs->item[0];                                        // 取得子節點            
    char var1[100], var2[100], tempVar[100];                                                          
    GenCode(g, item1, var1);                                                    // 遞迴產生 ITEM
    if (node->childs->count > 1) {
      Tree* op = node->childs->item[1];                                        // 連續取得 (op ITEM)? 
      Tree* item2 = node->childs->item[2];                                                         
      GenCode(g, item2, var2);                                                  // 遞迴產生 ITEM        
      GenTempVar(g, tempVar);                                                   // 取得臨時變數，例如T0  
      GenPcode(g, "", op->value, var1, var2, tempVar);                          // 中間碼：例如 + sum i T0
      strcpy(var1, tempVar);                                                    // 傳回臨時變數，例如 T0  
    }                                                                                                 
    strcpy(rzVar, var1);                                                        // 傳回臨時變數，例如 T0  
  } else if (strPartOf(node->type, "|number|id|")) {                            // 處理 number, id 節點
    // 遇到變數或常數，傳回其 value 名稱。                                                         
    strcpy(rzVar, node->value);                                                 // 直接傳回 id 或 number
  } else if (node->childs != NULL) {                                            // 其他情況           
    // 其他狀況，若有子代則遞回處理                                                                
    int i;                                                                                         
    for (i=0; i<node->childs->count; i++)                                       // 遞迴處理所有子節點
      GenCode(g, node->childs->item[i], nullVar);
  }
  return NULL;
}

void GenData(Generator *g) { // 產生組合語言的變數宣告 
  Array *symArray = HashTableToArray(g->symTable);
  int i;
  for (i=0; i<symArray->count; i++) { // 產生符號表 
    char *varName = symArray->item[i];
    char varLabel[100];
    sprintf(varLabel, "%s:", varName);
    GenAsmCode(g, varLabel, "RESW", "1", "", "");
  }
  for (i=0; i<g->varCount; i++) { // 產生臨時變數 
    char tVarLabel[100];
    sprintf(tVarLabel, "T%d:", i);
    GenAsmCode(g, tVarLabel, "RESW", "1", "", "");
  }
  ArrayFree(symArray, NULL);
}

void GenPcode(Generator *g, char* label, char* op, char* p1, char* p2, char* pTo) {        // 輸出pcode後再轉為組合語言        
  char labelTemp[100];                                                                                                      
  if (strlen(label)>0)                                                                                                      
    sprintf(labelTemp, "%s:", label);                                                                                       
  else                                                                                                                      
    strcpy(labelTemp, "");                                                                                                  
  printf("%-8s %-4s %-4s %-4s %-4s\n", labelTemp, op, p1, p2, pTo);                        // 印出 pcode                       
  GenPcodeToAsm(g, labelTemp, op, p1, p2, pTo);                                            // 將 pcode 轉為組合語言                                 
}                                                                                                        
                                                                                                                            
void GenPcodeToAsm(Generator *g, char* label, char* op, char* p1, char* p2, char* pTo) {   // 將 pcode 轉為組合語言的函數
  if (strlen(label)>0)                                                                     // 如果有標記                                       
    GenAsmCode(g, label, "", "", "", "");                                                  //  輸出標記                          
  if (strEqual(op, "=")) { // pTo = p1                                                     // 處理等號 (= 0 sum)                
    GenAsmCode(g, "", "LD", "R1", p1, "");                                                 // 轉成 LDI R1, 0                   
    GenAsmCode(g, "", "ST", "R1", pTo, "");                                                //      ST R1, sum                  
  } else if (strPartOf(op, "|+|-|*|/|")) { // pTo = p1 op p2                               // 處理運算(+ sum i sum)            
    char asmOp[100];                                                                                                        
    if (strEqual(op, "+")) strcpy(asmOp, "ADD");                                           // 根據 op 設定運算指令             
    else if (strEqual(op, "-")) strcpy(asmOp, "SUB");                                                                       
    else if (strEqual(op, "*")) strcpy(asmOp, "MUL");                                                                       
    else if (strEqual(op, "/")) strcpy(asmOp, "DIV");                                                                       
    GenAsmCode(g, "", "LD", "R1", p1, "");                                                 // 轉成 LD R1, sum                  
    GenAsmCode(g, "", "LD", "R2", p2, "");                                                 //      LD R2, i                    
    GenAsmCode(g, "", asmOp,"R3", "R1", "R2");                                             //      ADD R3, R1, R2              
    GenAsmCode(g, "", "ST", "R3", pTo, "");                                                //      ST R3, sum                  
  } else if (strEqual(op, "CMP")) { // CMP p1, p2                                          // 處理 CMP (cmp i 10)              
    GenAsmCode(g, "", "LD", "R1", p1, "");                                                 // 轉成 LD R1, i                    
    GenAsmCode(g, "", "LD", "R2", p2, "");                                                 //      LDI R2, 10                  
    GenAsmCode(g, "", "CMP", "R1", "R2", "");                                              //      CMP R1, R2                  
  } else if (strEqual(op, "J")) { // J op label                                            // 處理 J (J > _FOR)                
    char asmOp[100];                                                                       // 根據 op 設定跳躍指令             
    if (strEqual(p1, "=")) strcpy(asmOp, "JEQ");                                                   
    else if (strEqual(p1, "!=")) strcpy(asmOp, "JNE");                                                                      
    else if (strEqual(p1, "<")) strcpy(asmOp, "JLT");                                                                       
    else if (strEqual(p1, ">")) strcpy(asmOp, "JGT");                                                                       
    else if (strEqual(p1, "<=")) strcpy(asmOp, "JLE");                                                                      
    else if (strEqual(p1, ">=")) strcpy(asmOp, "JGE");                                                                      
    else strcpy(asmOp, "JMP");                                                                                              
    GenAsmCode(g, "", asmOp, pTo, "", "");                                                                                   
  } else if (strEqual(op, "RET")) {                                                        // 處理 RET sum                     
    GenAsmCode(g, "", "LD", "R1", pTo, "");                                                // 轉成 LD R1, sum                  
    GenAsmCode(g, "", "RET", "", "", "");                                                  //      RET                         
  }                                                                                                         
}                                                                                                  
                                                                                                                            
void GenAsmCode(Generator *g, char* label, char* op, char* p1, char* p2, char* pTo) {      // 輸出組合語言指令                                     
  char *realOp = op;                                                                                                                            
  if (strEqual(op, "LD"))                                                                                                   
    if (isdigit(p2[0]))                                                                    // 如果指令是 LD，而且              
      realOp = "LDI";                                                                      //   p2 為常數                      
  fprintf(g->asmFile, "%-8s %-4s %-4s %-4s %-4s\n", label, realOp, p1, p2, pTo);           //    改用 LDI 指令                 
}                                                                                          // 輸出組合語言指令                 
                                                                                                        
void GenTempVar(Generator *g, char *tempVar) {                                                          
  sprintf(tempVar, "T%d", g->varCount++);
}

void negateOp(char *condOp, char *negOp) {
  if (strEqual(condOp, "==")) strcpy(negOp, "!=");
  if (strEqual(condOp, "!=")) strcpy(negOp, "==");
  if (strEqual(condOp, ">=")) strcpy(negOp, "<");
  if (strEqual(condOp, "<=")) strcpy(negOp, ">");
  if (strEqual(condOp, ">")) strcpy(negOp, "<=");
  if (strEqual(condOp, "<")) strcpy(negOp, ">=");
}
