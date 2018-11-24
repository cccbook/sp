#include "Assembler.h"

void assemble(char *asmFile, char *objFile) {                   // 組譯器的主要函數
  printf("Assembler:asmFile=%s objFile=%s\n", asmFile,objFile); // 輸入組合語言、輸出目的檔
  printf("===============Assemble=============\n");
  char *text = newFileStr(asmFile);                             // 讀取檔案到 text 字串中
  Assembler *a = AsmNew();                                      
  AsmPass1(a, text);                                            // 第一階段：計算位址 
  printf("===============SYMBOL TABLE=========\n");             
  HashTableEach(a->symTable, (FuncPtr1) AsmCodePrintln);        // 印出符號表   
  AsmPass2(a);                                                  // 第二階段：建構目的碼 
  AsmSaveObjFile(a, objFile);                                      
  AsmFree(a);                                                   // 輸出目的檔   
  freeMemory(text);                                             // 釋放記憶體   
}                                                               

Assembler* AsmNew() {
  Assembler *a=ObjNew(Assembler, 1);
  a->codes = ArrayNew(10);
  a->symTable = HashTableNew(127);
  a->opTable = OpTableNew();
  return a;
}

void AsmFree(Assembler *a) {
  ArrayFree(a->codes, (FuncPtr1) AsmCodeFree);
  HashTableFree(a->symTable);
  OpTableFree();
  ObjFree(a);
}

void AsmPass1(Assembler *a, char *text) {             // 第一階段的組譯           
  int i, address = 0, number;                                                 
  Array* lines = split(text, "\r\n", REMOVE_SPLITER); // 將組合語言分割成一行一行
  ArrayEach(lines, strPrintln);                       // 印出以便觀察           
  printf("=================PASS1================\n");               
  for (i=0; i<lines->count; i++) {                    // 對於每一行                        
      strReplace(lines->item[i], SPACE, ' ');                   
      AsmCode *code = AsmCodeNew(lines->item[i]);     // 建立指令物件
      code->address = address;                        // 設定該行的位址      
      Op *op = HashTableGet(opTable, code->op);       // 查詢運算碼            
      if (op != NULL) {                               // 如果查到
        code->opCode = op->code;                      //    設定運算碼
        code->type = op->type;                        //    設定型態
      }                                                  
      if (strlen(code->label)>0)                      // 如果有標記符號
        HashTablePut(a->symTable, code->label, code); //    加入符號表中
      ArrayAdd(a->codes, code);                       //  建構指令物件陣列
      AsmCodePrintln(code);                           //    印出觀察
      code->size = AsmCodeSize(code);                 //  計算指令大小
      address += code->size;                          //  計算下一個指令位址
  }                                                                           
  ArrayFree(lines, strFree);                          // 釋放記憶體
}

void AsmPass2(Assembler *a) {                         // 組譯器的第二階段
  printf("=============PASS2==============\n");                       
  int i;                                                              
  for (i=0; i<a->codes->count; i++) {                 // 對每一個指令    
    AsmCode *code = a->codes->item[i];                                
    AsmTranslateCode(a, code);                        //   進行編碼動作  
    AsmCodePrintln(code);
  }
}

void AsmTranslateCode(Assembler *a, AsmCode *code) {                       // 指令的編碼函數           
  char p1[100], p2[100], p3[100], pt[100];                                                       
  int ra=0, rb=0, rc=0, cx=0;                                                  
  char cxCode[9]="00000000", objCode[100]="", args[100]="";                    
  strcpy(args, code->args);                                                    
  strReplace(args, ",", ' ');                                                  
  int pc = code->address + 4;                                              // 提取後PC為位址+4         
  switch (code->type) {                                                    // 根據指令型態             
    case 'J' :                                                             // 處理 J 型指令              
      if (!strEqual(args, "")) {                                                                    
        AsmCode *labelCode = HashTableGet(a->symTable,args);               //   取得符號位址            
        cx = labelCode->address - pc;                                      //   計算 cx 欄位            
        sprintf(cxCode, "%8x", cx);                                                                 
      }                                                                                             
      sprintf(objCode, "%2x%s", code->opCode, &cxCode[2]);                 //   編出目的碼(16進位)      
      break;                                                                                        
    case 'L' :                                                                                      
      sscanf(args, "R%d %s", &ra, p2);                                        
      if (strHead(p2, "[")) {                                                  
        sscanf(p2, "[R%d+%s]", &rb, pt);                                       
        if (sscanf(pt, "R%d", &rc)<=0)                                         
          sscanf(pt, "%d", &cx);                                               
      } else if (sscanf(p2, "%d", &cx)>0) {                                    
      } else {                                                             
        AsmCode *labelCode = HashTableGet(a->symTable, p2);                    
        cx = labelCode->address - pc;                                      
        rb = 15; // R[15] is PC                                            
      }                                                                         
      sprintf(cxCode, "%8x", cx);                                              
      sprintf(objCode, "%2x%x%x%s", code->opCode, ra, rb, &cxCode[4]);         
      break;                                                               
    case 'A' :                                                             // 處理 A 型指令         
      sscanf(args, "%s %s %s", p1, p2, p3);                                //   取得參數            
      sscanf(p1, "R%d", &ra);                                              //   取得ra暫存器代號    
      sscanf(p2, "R%d", &rb);                                              //   取得rb暫存器代號    
      if (sscanf(p3, "R%d", &rc)<=0)                                       //   取得rc暫存器代號    
        sscanf(p3, "%d", &cx);                                             //   或者是 cx 參數      
      sprintf(cxCode, "%8x", cx);                                                                   
      sprintf(objCode, "%2x%x%x%x%s", code->opCode,ra,rb,rc,&cxCode[5]);   //   編出目的碼(16進位)  
      break;                                                                                        
    case 'D' : {                                                           // 處理是資料宣告                             
      // 我們將資料宣告  RESW, RESB, WORD, BYTE 也視為一種指令，其形態為 D
      char format4[]="%8x", format1[]="%2x", *format = format1;            
      switch (code->opCode) {                                              // 如果是 RESW    
        case OP_RESW:                                                      //       或 RESB 
        case OP_RESB:                                                      //         
          memset(objCode, '0', code->size*2);                              // 目的碼為 0000….
          objCode[code->size*2] = '\0';
          break;                                                           // 如果是 WORD:            
        case OP_WORD:                                                                
          format = format4;                                                // 設定輸出格式為 %8x 
        case OP_BYTE: {                                                    // 如果是 BYTE : 輸出格式為 %2x
          Array *array = split(args, " ", REMOVE_SPLITER);                 //   其目的碼為每個數字轉為16進位的結果
          char *objPtr = objCode;
          int i=0;
          for (i=0; i<array->count; i++) {                                 
              char *item = array->item[i];
              if (isdigit(item[0]))
                sprintf(objPtr, format, atoi(item));
              else {
                AsmCode *itemCode = HashTableGet(a->symTable, item);
                sprintf(objPtr, format, itemCode->address);
              }
              objPtr += strlen(objPtr);
          }
          ArrayFree(array, strFree);
          break;
        } // case OP_BYTE:
      } // switch
      break;
    } // case 'D'
    default: 
      strcpy(objCode, "");
      break;
  }
  strReplace(objCode, " ", '0');
  strToUpper(objCode);
  code->objCode = newStr(objCode);
}

void AsmSaveObjFile(Assembler *a, char *objFile) {
  printf("==========Save to ObjFile:%s==========\n", objFile);
  FILE *file = fopen(objFile, "wb");
  int i;
  for (i=0; i<a->codes->count; i++) {
    AsmCode *code = a->codes->item[i];
    char *objPtr = code->objCode;
    while (*objPtr != '\0') {
      int x;
      sscanf(objPtr, "%2x", &x);
      assert(x >= 0 && x < 256);
      BYTE b = (BYTE) x;
      fwrite(&b, sizeof(BYTE), 1, file);
      objPtr += 2;
      char bstr[3];
      sprintf(bstr, "%2x", b);
      strReplace(bstr, " ", '0');
      strToUpper(bstr);
      printf("%s", bstr);
    }
  }
  printf("\n");
  fclose(file);
}

int AsmCodePrintln(AsmCode *code) {
  char label[100] = "", address[100], buffer[200];
  if (strlen(code->label)>0)
    sprintf(label, "%s:", code->label);
  sprintf(address, "%4x", code->address);
  strReplace(address, " ", '0');
  sprintf(buffer, "%s %-8s %-4s %-14s %c %2x %s\n", address, label, code->op, code->args, code->type, code->opCode, code->objCode);
  strToUpper(buffer);
  printf(buffer);
}

AsmCode* AsmCodeNew(char *line) {
  AsmCode* code = ObjNew(AsmCode,1);
  char label[100]="", op[100]="", args[100]="", temp[100];
  int count = sscanf(line, "%s %s %[^;]", label, op, args);
  if (strTail(label, ":")) {
    strTrim(temp, label, ":");
    strcpy(label, temp);
  } else {
    strcpy(label, "");
    sscanf(line, "%s %[^;]", op, args);
  }
//  printf("label=%s op=%s args=%s\n", code->label, op, args);
  code->label = newStr(label);
  code->op = newStr(op);
  strTrim(temp, args, SPACE);
  code->args = newStr(temp);
  code->type = ' ';
  code->opCode = OP_NULL;
//  AsmCodePrintln(code);
  return code;
}

void AsmCodeFree(AsmCode *code) {
  freeMemory(code->label);
  freeMemory(code->op);
  freeMemory(code->args);
  freeMemory(code->objCode);
  freeMemory(code);
}

int AsmCodeSize(AsmCode *code) {                    // 計算指令的大小     
  switch (code->opCode) {                           // 根據運算碼 op                       
    case OP_RESW :                                  //  如果是RESW       
      return 4 * atoi(code->args);                  //   大小為 4*保留量  
    case OP_RESB :                                  // 如果是RESB        
      return atoi(code->args);                      //   大小為 1*保留量  
    case OP_WORD :                                  // 如果是WORD        
      return 4 * (strCountChar(code->args, ",")+1); //   大小為 4*參數個數
    case OP_BYTE :                                  // 如果是BYTE        
      return strCountChar(code->args, ",")+1;       //   大小為1*參數個數                  
    case OP_NULL :                                  // 如果只是標記                      
      return 0;                                     //   大小為 0        
    default :                                       // 其他情形 (指令)   
      return 4;                                     //   大小為 4
  }                                                   
}
