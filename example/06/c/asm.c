#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include "c6.h"

Pair dList[] = {
  {"", "000"}, {"M", "001"}, {"D", "010"}, {"MD", "011"},
  {"A","100"}, {"AM","101"}, {"AD","110"}, {"AMD","111"}
};

Pair cList[] = {
  {"0",   "0101010"}, {"1",   "0111111"}, {"-1",  "0111010"},
  {"D",   "0001100"}, {"A",   "0110000"}, {"!D",  "0001101"},
  {"!A",  "0110001"}, {"-D",  "0001111"}, {"-A",  "0110011"},
  {"D+1", "0011111"}, {"A+1", "0110111"}, {"D-1", "0001110"},
  {"A-1", "0110010"}, {"D+A", "0000010"}, {"D-A", "0010011"},
  {"A-D", "0000111"}, {"D&A", "0000000"}, {"D|A", "0010101"},
  {"M",   "1110000"}, {"!M",  "1110001"}, {"-M",  "1110011"},
  {"M+1", "1110111"}, {"M-1", "1110010"}, {"D+M", "1000010"},
  {"D-M", "1010011"}, {"M-D", "1000111"}, {"D&M", "1000000"},
  {"D|M", "1010101"}
};

Pair jList[] = {
  {"",   "000"}, {"JGT","001"}, {"JEQ","010"}, {"JGE","011"},
  {"JLT","100"}, {"JNE","101"}, {"JLE","110"}, {"JMP","111"}
};

#define SYM_SIZE 1000*100

int addr[SYM_SIZE] = {
  0, 1, 2, 3,
  4, 5, 6, 7,
  8, 9, 10, 11, 
  12, 13, 14, 15,
  16384, 24576, 
  0, 1, 2, 3, 4
};

Pair symList[SYM_SIZE] = {
  {"R0",&addr[0]},{"R1",&addr[1]},{"R2",&addr[2]},{"R3",&addr[3]}, 
  {"R4",&addr[4]},{"R5",&addr[5]},{"R6",&addr[6]},{"R7",&addr[7]},
  {"R8",&addr[8]}, {"R9",&addr[9]}, {"R10",&addr[10]}, {"R11",&addr[11]},
  {"R12",&addr[12]}, {"R13",&addr[13]}, {"R14",&addr[14]}, {"R15",&addr[15]},
  {"SCREEN",&addr[16]}, {"KBD",&addr[17]}, {"SP",&addr[18]}, {"LCL",&addr[19]}, 
  {"ARG",&addr[20]}, {"THIS",&addr[21]}, {"THAT",&addr[22]}
};

Map dMap, cMap, jMap, symMap;
int symTop = 23;
int varTop = 16;

char strTableText[100000];
StrTable strTable;

void symAdd(Map *map, char *label, int address) {
  addr[map->top] = address;
  Pair p = c6mapAdd(map, c6strNew(&strTable, label), &addr[map->top]);
  printf("  p.key=%s *p.value=%d top=%d\n", p.key, *(int*)p.value, map->top);
}

void symDump(Map *map) {
  printf("======= SYMBOL TABLE ===========\n");
  for (int i=0; i<map->top; i++) {
    char *key = map->list[i].key;
    int *vptr = map->list[i].value;
    printf("%d: %s, %d\n", i, key, *vptr);
  }
}

char *parse(string line) {
  char *codePtr = line, *codeEnd = line;
  while (strchr("\t ", *codePtr) != NULL) codePtr++;
  while (*codeEnd != '\0' && strchr("/\n\r", *codeEnd) == NULL) codeEnd++;
  *codeEnd = '\0';
  return codePtr;
}

void code2binary(string code, string binary) {
  char d[10], comp[100], j[10];
  string dcode, ccode, jcode;
  if (code[0]=='@') { // A 指令： ＠number || @symbol
    int address;
    int match = sscanf(code, "@%d", &address);
    if (match == 1)
      c6itob(address, binary);
    else {
      char symbol[100];
      match = sscanf(code, "@%s", symbol);
      int* addrPtr = c6mapLookup(&symMap, symbol);
      if (addrPtr == NULL) { // 宣告變數
        symAdd(&symMap, symbol, varTop); // 新增一個變數
        address = varTop++;
      } else { // 已知變數 (標記) 位址
        address = *addrPtr;
      }
      c6itob(address, binary);
    }
  } else { // C 指令
    if (strchr(code, '=') != NULL) { // d=comp
      sscanf(code, "%[^=]=%s", d, comp);
      dcode = c6mapLookup(&dMap, d);
      ccode = c6mapLookup(&cMap, comp);
      sprintf(binary, "111%s%s000", ccode, dcode);
    } else {
      sscanf(code, "%[^;];%s", comp, j); // comp;j
      ccode = c6mapLookup(&cMap, comp);
      jcode = c6mapLookup(&jMap, j);
      sprintf(binary, "111%s000%s", ccode, jcode);      
    }
  }
}

void pass1(string inFile) {
  printf("============= PASS1 ================\n");
  char line[100]="";
  FILE *fp = fopen(inFile, "r");
  int address = 0;
  while (fgets(line, sizeof(line), fp)) {
    char *code = parse(line);
    if (strlen(code)==0) continue;
    printf("%02d:%s\n", address, code);
    if (code[0] == '(') {
      char label[100];
      sscanf(code, "(%[^)])", label);
      symAdd(&symMap, label, address);
    } else {
      address ++;
    }
  }
  fclose(fp);
}

void pass2(string inFile, string hackFile, string binFile) {
  printf("============= PASS2 ================\n");
  char line[100], binary[17];
  FILE *fp = fopen(inFile, "r");
  FILE *hfp = fopen(hackFile, "w");
  FILE *bfp = fopen(binFile, "wb");
  while (fgets(line, sizeof(line), fp)) {
    char *code = parse(line);
    if (strlen(code)==0) continue;
    if (code[0] == '(') {
      printf("%s\n", code);
    } else {
      code2binary(code, binary);
      uint16_t b = c6btoi(binary);
      printf("  %-20s %s %04x\n", code, binary, b);
      fprintf(hfp, "%s\n", binary);
      fwrite(&b, sizeof(b), 1, bfp);
    }
  }
  fclose(fp);
  fclose(hfp);
  fclose(bfp);
}

void assemble(string file) {
  char inFile[100], hackFile[100], binFile[100];
  sprintf(inFile, "%s.asm", file);
  sprintf(hackFile, "%s.hack", file);
  sprintf(binFile, "%s.bin", file);
  symDump(&symMap);
  pass1(inFile);
  symDump(&symMap);
  pass2(inFile, hackFile, binFile);
}

// run: ./asm <file> 
// notice : <file> with no extension.
int main(int argc, char *argv[]) {
  c6mapNew(&dMap, dList, c6size(dList));
  c6mapNew(&cMap, cList, c6size(cList));
  c6mapNew(&jMap, jList, c6size(jList));
  c6mapNew(&symMap, symList, SYM_SIZE);
  c6strTable(&strTable, strTableText, c6size(strTableText));
  symMap.top = symTop;
  assemble(argv[1]);
}
