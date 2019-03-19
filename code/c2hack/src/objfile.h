// 簡化的 ELF 目的檔

#ifndef __OBJFILE_H__
#define __OBJFILE_H__

typedef uint16_t Elf16_Word
typedef uint16_t Elf16_Off
typedef uint16_t Elf16_Addr

typedef struct {
  Elf16_Off         e_shoff;                // 分段表頭的位址
  Elf16_Half        e_shentsize;            // 分段表頭的記錄長度
  Elf16_Half        e_shnum;                // 分段表頭的記錄個數
  Elf16_Half        e_shstrndx;             // 分段字串表 .shstrtab 的分段代號
} Elf16_Ehdr;

typedef struct {
  Elf16_Word    sh_type;                    // 分段類型
  Elf16_Off     sh_offset;                  // 分段位移 (在目的檔中的位址)
  Elf16_Word    sh_size;                    // 分段大小
} Elf16_Shdr;

#endif