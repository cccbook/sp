#include "objfile.h"

int objNew(ObjFile *obj, Map *symTable, StrTable *strTable) {
  memset(obj, 0, sizeof(ObjFile));
  obj->symTable = symTable;
  obj->strTable = strTable;

  Elf16_Ehdr *ehdr = &obj->ehdr;
  ehdr->e_shoff = sizeof(Elf16_Ehdr);            // 分段表緊接 Ehdr 之後。
  ehdr->e_shnum = SECTIONS;                      // 共有五個分段 0:code, 1:data, 2:bss, 3:symTable, 4:strTable
  ehdr->e_shentsize = sizeof(Elf16_Shdr);        // 分段結構為 Elf16_Shdr，所以大小為 sizeof(Elf16_Shdr)
  ehdr->e_shstrndx = 4;                          // 字串表在第四段

  Elf16_Shdr *shdrs = obj->shdrs;
  void **bin = obj->bin;
  shdrs[CODE].sh_type = CODE;     bin[CODE]   = obj->codeBin;    // 第 0 段為 CODE
  shdrs[DATA].sh_type = DATA;     bin[DATA]   = obj->dataBin;    // 第 1 段為 DATA
  shdrs[BSS].sh_type = BSS;       bin[BSS]    = obj->bssBin;     // 第 2 段為 BSS
  shdrs[SYMTAB].sh_type = SYMTAB; bin[SYMTAB] = obj->symBin;     // 第 3 段為 SYMTAB
  shdrs[STRTAB].sh_type = STRTAB; bin[STRTAB] = strTable->text;  // 第 4 段為 STRTAB
}

int symToBin(Map *map, Elf16_Word *bin, StrTable *strTable) {
  Pair *table = map->table;
  int i;
  for (i=0; i<map->size; i++) {
    char *name = table[i].key;
    Elf16_Off offset = name - strTable->text;
    bin[i] = offset;
  }
  return i * sizeof(bin[0]);
}

int objSave(ObjFile *obj, char *objName) {
  FILE *oFile = fopen(objName, "w");
  Elf16_Shdr *shdrs = obj->shdrs;

  shdrs[SYMTAB].sh_size = symToBin(obj->symTable, obj->symBin, obj->strTable);
  shdrs[STRTAB].sh_size = stSize(obj->strTable);

  fwrite(&obj->ehdr, sizeof(obj->ehdr), 1, oFile);  // header
  fwrite(obj->shdrs, sizeof(obj->shdrs), 1, oFile); // section header
  for (int i=0; i<SECTIONS; i++) {
    fwrite(obj->bin[i], shdrs[i].sh_size, 1, oFile); // section
  }

  fclose(oFile);
}
/*
int objLoad(ObjFile *obj, char *objName) {
  FILE *oFile = fopen(objName, "r");

  fread(&obj->ehdr, sizeof(obj->ehdr), 1, oFile);
  fread(obj->shdrs, sizeof(obj->shdrs), 1, oFile);

  fread(obj->codeBin, obj->codeSize, 1, oFile);  // code
  fread(obj->dataBin, obj->dataSize, 1, oFile);  // data
  fread(symBin, symSize, 1, oFile);              // symTable
  fread(obj->strTable->text, strSize, 1, oFile); // strTable

  fclose(oFile);
}

int objDump(ObjFile *obj) {

}
*/