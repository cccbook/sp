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
  debug("\n  key=%s *value=%d top=%d\n", p->key, *(int*)p->value, map->top);
}

void symDump(Map *map) {
  debug("======= SYMBOL TABLE ===========\n");
  debug("map->top = %d size=%d\n", map->top, map->size);
  for (int i=0; i<map->size; i++) {
    Pair *p = &map->table[i];
    if (p->key != NULL)
      debug("%d: %s, %d\n", i, p->key, *(int*) p->value);
  }
}

void parseLabelData(Code *c, char *line) {
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
  for (int i=0; (p = c->dstr[i]); i++) { // 注意： p 改指向 dstr[i] 了
    c->bptr[i] = b;
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
        int n;
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
}

int parse(char *line, Code *c) {
  memset(c, 0, sizeof(Code));
  c->line = line;
  replace(line, "\r\t\n", ' ');
  char *p = line;
  char *pend = strstr(p, "//");  // 去掉註解
  if (pend) *pend = '\0';
  for (; *p!='\0'; p++) { // 找到第一個不是空白的字
    if (*p!=' ') break;
  }
  c->size = 1;
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

// ex: comp: D+A, code: {a,c} = {0,code(D+A)}
// ex: comp: D+M, code: {a,c} = {1,code(D+A)}
void comp2code(char *comp, char *code) {
  char *aComp = comp, mComp[100], *c;
  c = mapLookup(&cMap, aComp); // A: 0xxxxxx
  if (c) { // {a=0 /*A*/}
    sprintf(code, "0%s", c);
    return;
  }
  strcpy(mComp, comp); replace(mComp, "M", 'A');
  c = mapLookup(&cMap, mComp); // M: 1xxxxxx
  if (c) { // {a=1 /*M*/ }
    sprintf(code, "1%s", c); /*D+M*/;
    return;
  }
  error("comp=%s or %s not found!", aComp, mComp);
}

void code2bin(Code *c) {
  char bstr[100]; uint16_t *bin = c->bin;
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
      if (!dcode) error("code2bin: c->d=%s not found!", c->d);
      comp2code(c->c, ccode);
      sprintf(bstr, "111%s%s%s", ccode, dcode, jcode);
    } else { // c;j
      comp2code(c->c, ccode);
      char *jcode = "000";
      if (c->j) jcode = mapLookup(&jMap, c->j);
      if (!jcode) error("code2bin: jcode=%s not found!", jcode);
      sprintf(bstr, "111%s%s%s", ccode, dcode, jcode);
    }
    bin[0] = btoi(bstr);
  } else if (c->label) { // LABEL : 把符號轉成位址
    for (int i=0; c->dstr[i]; i++) { // i < c->dsize
      if (c->dtype[i] == 'L') {
        uint16_t *address = mapLookup(&symMap, c->dstr[i]);
        *(c->bptr[i]) = *address;
      }
    }
  }
}

void pass1(string inFile) {
  debug("============= PASS1 ================\n");
  char line[100]="";
  FILE *fp = fopen(inFile, "r");
  int address = 0;
  while (fgets(line, sizeof(line), fp)) {
    Code code;
    replace(line, "\r\n", ' ');
    debug("%02d:%s\n", address, line);
    parse(line, &code);
    if (code.label) {
      debug("label=%s address=%02X\n", code.label, address);
      symAdd(&symMap, code.label, address);
    }
    address += code.size;
  }
  fclose(fp);
}

void pass2(string inFile, string binFile) {
  debug("============= PASS2 ================\n");
  char line[100];
  FILE *fp = fopen(inFile, "r");
  FILE *bfp = fopen(binFile, "wb");
  int address = 0;
  while (fgets(line, sizeof(line), fp)) {
    Code code;
    replace(line, "\r\n", ' ');
    debug("%04X %-20s", address, line);
    if (!parse(line, &code)) { debug("\n"); continue; }
    code2bin(&code);
    if (isDebug) hexDump16(code.bin, code.size);
    debug("\n");
    if (code.size > 0) fwrite(code.bin, code.size*2, 1, bfp);
    address += code.size;
  }
  fclose(fp);
  fclose(bfp);
}

void assemble(string file) {
  char inFile[100], binFile[100];
  sprintf(inFile, "%s.s0", file);
  sprintf(binFile, "%s.o0", file);
  symDump(&symMap);
  pass1(inFile);
  symDump(&symMap);
  pass2(inFile, binFile);
  symDump(&symMap);
}

// run: ./asm <file> 
// notice : <file> with no extension.
int main(int argc, char *argv[]) {
  argHandle(argc, argv, 2, "./asm <file>\n");
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
