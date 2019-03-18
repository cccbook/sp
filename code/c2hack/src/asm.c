#include "asm.h"

Pair dList[] = {
  {"", "000"}, {"M", "001"}, {"D", "010"}, {"MD", "011"},
  {"A","100"}, {"AM","101"}, {"AD","110"}, {"AMD","111"}
};

Pair cList[] = {
  {"0",   "101010"}, {"1",   "111111"}, {"-1",  "111010"},
  {"D",   "001100"}, {"!D",  "001101"}, {"-D",  "001111"},
  {"D+1", "011111"}, {"D-1", "001110"},
  {"A",   "110000"},
  {"!A",  "110001"},
  {"-A",  "110011"},
  {"D-A", "010011"},
  {"D+A", "000010"},
  {"D&A", "000000"},
  {"D|A", "010101"},
  {"A+1", "110111"},
  {"A-1", "110010"},
  {"A-D", "000111"},
  // Extension instruction : 使用 10 開頭，避開 {"0",   "101010"}
  {"D<<A", "100000"},
  {"D>>A", "100001"},
  {"D*A",  "100010"},
  {"D/A",  "100011"},
  {"D%A",  "100100"},
  {"D<A",  "100101"},
  {"D<=A", "100110"},
  {"D>A",  "100111"},
  {"D>=A", "101000"},
  {"D==A", "101001"},
  {"D!=A", "101011"},
  {"D^A",  "101100"},
  {"call", "101101"},
  {"ret",  "101110"},
  {"swi",  "101111"},
  // io 指令 : I[14]=1 使用 CPU，I[14]=0 使用 IO 指令，所以不需要再避免衝突了。
  // {".swi", "000001"}, // 
  // {".puts", "000001"}, 
  /*
  {"gets", "010001"},
  {"puti", "010010"},
  {"putf", "011000"},
  {"addf", "011001"},
  {"subf", "011010"},
  {"mulf", "011011"},
  {"divf", "011100"},
  */
};

Pair jList[] = {
  {"",   "000"}, {"JGT","001"}, {"JEQ","010"}, {"JGE","011"},
  {"JLT","100"}, {"JNE","101"}, {"JLE","110"}, {"JMP","111"}
};


int addr[SYM_SIZE] = {
  0, 1, 2, 3,
  4, 5, 6, 7,
  8, 9, 10, 11, 
  12, 13, 14, 15,
  16384, 24576, 
  0, 1, 2, 3, 4
};

Pair symList[] = {
  {"R0",&addr[0]},{"R1",&addr[1]},{"R2",&addr[2]},{"R3",&addr[3]}, 
  {"R4",&addr[4]},{"R5",&addr[5]},{"R6",&addr[6]},{"R7",&addr[7]},
  {"R8",&addr[8]}, {"R9",&addr[9]}, {"R10",&addr[10]}, {"R11",&addr[11]},
  {"R12",&addr[12]}, {"R13",&addr[13]}, {"R14",&addr[14]}, {"R15",&addr[15]},
  {"SCREEN",&addr[16]}, {"KBD",&addr[17]}, {"SP",&addr[18]}, {"LCL",&addr[19]}, 
  {"ARG",&addr[20]}, {"THIS",&addr[21]}, {"THAT",&addr[22]}
};

Map dMap, cMap, jMap, symMap;
int varTop = 16;

void symAdd(Map *map, char *label, int address) {
  addr[map->top] = address;
  Pair *p = mapAdd(map, stAdd(label), &addr[map->top]);
  printf("  key=%s *value=%d top=%d\n", p->key, *(int*)p->value, map->top);
}

void symDump(Map *map) {
  printf("======= SYMBOL TABLE ===========\n");
  printf("map->top = %d size=%d\n", map->top, map->size);
  for (int i=0; i<map->size; i++) {
    Pair *p = &map->table[i];
    if (p->key != NULL)
      printf("%d: %s, %d\n", i, p->key, *(int*) p->value);
  }
}

int parseLabelData(Code *c, char *line) {
  char *p = line;
  assert(*p == '(');
  c->type = 'L';
  char *token = c->label = strtok(++p, ")");

  int i;
  for (i=0; token  != NULL; i++) {
    p = token = strtok(NULL, ",");
    if (token) {
      while (*p == ' ') p++;
    }
    c->dstr[i] = (p && *p!='\0') ? p : NULL;
  }

  uint16_t *b = c->bin;
  for (int i=0; p=c->dstr[i]; i++) { // 注意： p 改指向 dstr[i] 了
    c->bptr[i] = b;
    // printf("c->dstr[%d]=%s\n", i, c->dstr[i]);
    if (*p == '"') { // 字串 "..." 
      c->dtype[i] = 'S';
      for (++p; *p != '"' && *p != '\0'; ) *b++ = *p++;
    } else if (isdigit(*p)) {
      if (strchr(p, '.')) { // 浮點數，大小為 2
        float f;
        c->dtype[i] = 'F';
        sscanf(p, "%f", &f);
        uint16_t *tf = (uint16_t*) &f;
        *b++ = tf[0];
        *b++ = tf[1];
      } else {
        int16_t n;
        sscanf(p, "%d", &n);
        c->dtype[i] = 'N';
        *b++ = n;
      }
    } else { // 應該是符號，暫時先放 0
      c->dtype[i] = 'L';
      *b++ = 0;
    }
  }
  c->size = b - c->bin;
  // printf("c->size=%d\n", c->size);
}

int parse(char *line, Code *c) {
  memset(c, 0, sizeof(Code));
  c->line = line;
  // printf("parse: line=%s\n", line);
  replace(line, "\r\t\n", ' ');
  char *p = line;
  char *pend = strstr(p, "//");  // 去掉註解
  if (pend) *pend = '\0';
  for (; *p!='\0'; p++) { // 找到第一個不是空白的字
    if (*p!=' ') break;
  }
  // printf("parse: p=%s\n", p);
  c->size = 1;
  char *begin = p;
  if (*p == '\0') { // 空行 : 不算大小
    c->size = 0;
  } else if (*p == '(') { // 如果是符號行 (L)
    parseLabelData(c, p);
  } else if (*p == '@') { // 如果是 A 指令
    c->type = 'A';
    c->a = strtok(++p, " ");
  } else { // 否則，就是 C 指令
    c->type = 'C';
    char *op1, *op2;
    op1 = strpbrk(p, "=;");
    if (op1 && *op1 == '=') {
      c->d = strtok(p, "=");
      p = op1 + 1;
    }
    op2 = strpbrk(p, ";");
    if (op2 && *op2 == ';') {
      c->c = strtok(p, ";");
      p = op2 + 1;
    }
    strtok(p, " ");
    // printf("d=%s c=%s p=%s\n", c->d, c->c, p);
    if (!op1 && !op2) {
      c->c = p;
    } else if (op1 && !op2) {
      c->c = op1 + 1;
    } else if (op2) {
      c->j = p;
    }
  }
  // printf("  parse code:type=%c label=%s a=%s d=%s c=%s j=%s\n", c->type, c->label, c->a, c->d, c->c, c->j);
  return c->size;
}

// ex: comp: D+A, code: {p,m,a,c} = {1,1,0,code(D+A)}
void comp2code(char *comp, char *code) {
  char *aComp = comp, mComp[100], iComp[100], *c;
  c = mapLookup(&cMap, aComp); // A: x10xxxxxx
  // printf("comp2code:comp=%s\n", comp);
  if (c) { // {p,m,a=0 /*A*/}
    char *head = (c[0] == '.')?"010"/*p=0:.puts */:"110" /*p=1:D+A*/;
    sprintf(code, "%s%s", head, c);
    return;
  }
  strcpy(mComp, comp); replace(mComp, "M", 'A');
  c = mapLookup(&cMap, mComp); // M: x11xxxxxx
  if (c) { // {p,m,a=1 /*M*/ }
    sprintf(code, "%s%s", "111", c); /*D+M*/;
    // printf("comp2code:mComp=%s code=%s\n", mComp, code);
    return;
  }
  strcpy(iComp, comp); replace(iComp, "I", 'A');
  c = mapLookup(&cMap, iComp); // I: x01xxxxxx
  if (c) {
    sprintf(code, "%s%s", "101", c); /*D+I*/
    return;
  }
  error("comp=%s not found!");
}

void code2bin(Code *c) {
  char bstr[100]; uint16_t *bin = c->bin;
  // printf("code2bin(): a=%s d=%s c=%s j=%s\n", c->a,  c->d, c->c,c->j);
  if (c->a) { // A 指令： ＠number || @symbol
    int A;
    if (isdigit(c->a[0])) {
      A = atoi(c->a);
      bin[0] = A;
    } else {
      char *symbol = c->a;
      int* addrPtr = mapLookup(&symMap, symbol);
      if (addrPtr == NULL) { // 宣告變數
        symAdd(&symMap, symbol, varTop); // 新增一個變數
        A = varTop ++;
      } else { // 已知變數 (標記) 位址
        A = *addrPtr;
      }
      bin[0] = A;
    }
  } else if (c->c) { // C 指令
    char ccode[20], *dcode="000", *jcode="000";
    if (c->d) { // d=c
      dcode = mapLookup(&dMap, c->d);
      if (!dcode) error("code2bin: dcode not found!", dcode);
      comp2code(c->c, ccode);
      // printf("ccode=%s dcode=%s\n", ccode, dcode);
      sprintf(bstr, "1%s%s%s", ccode, dcode, jcode);
    } else { // c;j
      comp2code(c->c, ccode);
      char *jcode = "000";
      if (c->j) jcode = mapLookup(&jMap, c->j);
      if (!jcode) error("code2bin: jcode=%s not found!", jcode);
      sprintf(bstr, "1%s%s%s", ccode, dcode, jcode);
    }
    // printf("C:bstr=%s\n", bstr);
    bin[0] = btoi(bstr);
    // printf("bstr=%s bin=0x%04X\n", bstr, bin[0]);
  } else if (c->label) { // LABEL : 把符號轉成位址
    int16_t *b = bin;
    for (int i=0; c->dstr[i]; i++) { // i < c->dsize
      if (c->dtype[i] == 'L') {
        uint16_t *address = mapLookup(&symMap, c->dstr[i]);
        *(c->bptr[i]) = *address;
      }
    }
  }
}

void pass1(string inFile) {
  printf("============= PASS1 ================\n");
  char line[100]="";
  FILE *fp = fopen(inFile, "r");
  int address = 0;
  while (fgets(line, sizeof(line), fp)) {
    Code code;
    replace(line, "\r\n", ' ');
    printf("%02d:%s\n", address, line);
    // if (!parse(line, &code)) continue;
    parse(line, &code);
    if (code.label) {
      printf("label=%s address=%02X\n", code.label, address);
      symAdd(&symMap, code.label, address);
      // printf("pass1:symAdd(%s)\n", code.label);
    }
    address += code.size;
  }
  fclose(fp);
}

void pass2(string inFile, string hackFile, string binFile) {
  printf("============= PASS2 ================\n");
  char line[100];
  FILE *fp = fopen(inFile, "r");
  FILE *hfp = fopen(hackFile, "w");
  FILE *bfp = fopen(binFile, "wb");
  int address = 0;
  while (fgets(line, sizeof(line), fp)) {
    Code code;
    replace(line, "\r\n", ' ');
    printf("%04X %-20s", address, line);
    if (!parse(line, &code)) { printf("\n"); continue; }
    code2bin(&code);
    hexDump16(code.bin, code.size);
    printf("\n");
    if (code.size > 0) fwrite(code.bin, code.size*2, 1, bfp);
    address += code.size;
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
  // 建置表格
  mapNew(&dMap, 37); mapAddAll(&dMap, dList, ARRAY_SIZE(dList));
  mapNew(&cMap, 79); mapAddAll(&cMap, cList, ARRAY_SIZE(cList));
  mapNew(&jMap, 23); mapAddAll(&jMap, jList, ARRAY_SIZE(jList));
  mapNew(&symMap, SYM_SIZE); mapAddAll(&symMap, symList, ARRAY_SIZE(symList));
  stInit();
  // 組譯器主要函數開始
  assemble(argv[1]);
  // 釋放表格
  mapFree(&dMap);
  mapFree(&cMap);
  mapFree(&jMap);
  mapFree(&symMap);
}

        /*    char str[100]; float f; int n;
              while (*p != '\0') {
        while (*p == ' ') p++;
        char *start = p, token = NULL;
        while (*p != ',' && *p != '\0') p++;
        scopy(token, data, token, p-token);

        if (sscanf(c->data, "\"%s\"", str) == 1) {
          c->tokens[i] = str
          c->size += strlen(str);
        } else if (sscanf(c->data, "%f", &f) == 1) {
          c->size = 2;
        } else if (sscanf(c->data, "%d", &n) == 1) c->size = 1;
      }
              */