#ifndef __ELF_H__
#define __ELF_H__
#include <stdint.h>

// 參考 -- https://github.com/torvalds/linux/blob/master/include/uapi/linux/elf.h

typedef uint16_t Elf16_Word
typedef uint16_t Elf16_Off
typedef uint16_t Elf16_Addr

typedef struct elf16_rel { // 重定位紀錄
  Elf16_Addr	r_offset;
  Elf16_Word	r_info;
} Elf16_Rel;

typedef struct elf16_sym { // 符號紀錄
  Elf16_Word	st_name;
  Elf16_Addr	st_value;
  Elf16_Word	st_size;
  unsigned char	st_info;
  unsigned char	st_other;
  Elf16_Half	st_shndx;
} Elf16_Sym;

typedef struct { // ELF 表頭
  unsigned char     e_ident[EI_NIDENT];     // ELF 辨識代號區
  Elf16_Half        e_type;                 // 檔案類型代號
  Elf16_Half        e_machine;              // 機器平台代號
  Elf16_Word        e_version;              // 版本資訊
  Elf16_Addr        e_entry;                // 程式的起始位址
  Elf16_Off         e_phoff;                // 程式表頭的位址
  Elf16_Off         e_shoff;                // 分段表頭的位址
  Elf16_Word        e_flags;                // 與處理器有關的旗標值
  Elf16_Half        e_ehsize;               // ELF檔頭的長度
  Elf16_Half        e_phentsize;            // 程式表頭的記錄長度
  Elf16_Half        e_phnum;                // 程式表頭的記錄個數
  Elf16_Half        e_shentsize;            // 分段表頭的記錄長度
  Elf16_Half        e_shnum;                // 分段表頭的記錄個數
  Elf16_Half        e_shstrndx;             // 分段字串表 .shstrtab 的分段代號
} Elf16_Ehdr;

typedef struct {
  Elf16_Word    sh_name;                    // 分段名稱代號
  Elf16_Word    sh_type;                    // 分段類型
  Elf16_Word    sh_flags;                   // 分段旗標
  Elf16_Addr    sh_addr;                    // 分段位址 (在記憶體中的位址)
  Elf16_Off     sh_offset;                  // 分段位移 (在目的檔中的位址)
  Elf16_Word    sh_size;                    // 分段大小
  Elf16_Word    sh_link;                    // 連結指標 (依據分段類型而定)
  Elf16_Word    sh_info;                    // 分段資訊
  Elf16_Word    sh_addralign;               // 對齊資訊
  Elf16_Word    sh_entsize;                 // 分段中的結構大小 (分段包含子結構時使用)
} Elf16_Shdr;

typedef struct {                   
   Elf16_Word p_type;                       // 分區類型
   Elf16_Off p_offset;                      // 分區位址 (在目的檔中)
   Elf16_Addr p_vaddr;                      // 分區的虛擬記憶體位址
   Elf16_Addr p_paddr;                      // 分區的實體記憶體位址
   Elf16_Word p_filesz;                     // 分區在檔案中的大小
   Elf16_Word p_memsz;                      // 分區在記憶體中的大小
   Elf16_Word p_flags;                      // 分區旗標
   Elf16_Word p_align;                      // 分區的對齊資訊
} Elf16_Phdr;

#endif