#include "objfile.h"

#define SECTIONS 5 // 共有五個分段 0:code, 1:data, 2:bss, 3:symTable, 4:strTable

#define CODE 0
#define DATA 1
#define BSS  2
#define SYMTAB 3
#define STRTAB 4

int objNew(Elf16_Ehdr *ehdr, Elf16_Shdr *shdrs) {
  ehdr->e_shoff = sizeof(Elf16_Ehdr);            // 分段表緊接 Ehdr 之後。
  ehdr->e_shnum = SECTIONS;                      // 共有五個分段 0:code, 1:data, 2:bss, 3:symTable, 4:strTable
  ehdr->e_shentsize = sizeof(Elf16_Shdr);        // 分段結構為 Elf16_Shdr，所以大小為 sizeof(Elf16_Shdr)
  ehdr->e_shstrndx = 4;                          // 字串表在第四段
  memset(shdrs, sizeof(Elf16_Shdr)*SECTIONS, 0); //
  shdrs[0].sh_type = CODE;
  shdrs[1].sh_type = DATA;
  shdrs[2].sh_type = BSS;
  shdrs[3].sh_type = SYMTAB;
  shdrs[4].sh_type = STRTAB;
}

