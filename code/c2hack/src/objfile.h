// 簡化的 ELF 目的檔

#ifndef __OBJFILE_H__
#define __OBJFILE_H__

#include <stdint.h>
#include "util.h"
#include "strTable.h"
#include "map.h"

typedef uint16_t Elf16_Word;
typedef uint16_t Elf16_Off;
typedef uint16_t Elf16_Addr;
typedef uint16_t Elf16_Half;

typedef struct {
  Elf16_Off     e_shoff;                // 分段表頭的位址
  Elf16_Half    e_shentsize;            // 分段表頭的記錄長度
  Elf16_Half    e_shnum;                // 分段表頭的記錄個數
  Elf16_Half    e_shstrndx;             // 分段字串表 .shstrtab 的分段代號
} Elf16_Ehdr;

typedef struct {
  Elf16_Word    sh_type;                    // 分段類型
  Elf16_Off     sh_offset;                  // 分段位移 (在目的檔中的位址)
  Elf16_Word    sh_size;                    // 分段大小
} Elf16_Shdr;

#define SECTIONS 5 // 共有五個分段 0:code, 1:data, 2:bss, 3:symTable, 4:strTable

#define CODE 0
#define DATA 1
#define BSS  2
#define SYMTAB 3
#define STRTAB 4

#define CODE_MAX 10240
#define DATA_MAX 10240
#define SYM_MAX 1024

typedef struct {
  Elf16_Ehdr ehdr;
  Elf16_Shdr shdrs[SECTIONS];
  void *bin[SECTIONS];
  Elf16_Word codeBin[CODE_MAX], dataBin[DATA_MAX], bssBin[1], symBin[SYM_MAX];
  // codeBin[BIN_MAX], dataBin[BIN_MAX];
  // Elf16_Off  symBin[TMAX];
  // Elf16_Off  codeSize, dataSize, bssSize, symSize, strSize;
  Map *symTable;
  StrTable *strTable;
} ObjFile;

extern int objNew(ObjFile *obj, Map *symTable, StrTable *strTable);
extern int mapToBin(Map *map, Elf16_Word *bin);
extern int objSave(ObjFile *obj, char *fileName);

#endif