#ifndef __VM_H__
#define __VM_H__

#include "strTable.h"
#include "map.h"
#include "util.h"
#include "scan.h"
#include "x86.h"

typedef struct _VmCode {
  char *op, *d, *p1, *p2;
  char *_d, *_p1, *_p2, *x;
} VmCode;

extern FILE *pFile; // 虛擬碼檔案
extern FILE *sFile; // x86 組合語言檔案
extern int vmCodeTop, argIdx, localTop, vmGlobalTop;
extern int labelIdx, tempIdx, tempMax; // 臨時變數數量
extern VmCode vmCodes[], vmGlobals[];
#define CODEMAX 100000
#define SYMMAX 10000
extern char *vmNextLabel(char *prefix);
extern char *vmNextTemp();
#define vmEmit(...) do { printf( __VA_ARGS__ ); fprintf(pFile, __VA_ARGS__); } while (0)
#define asmEmit(...) do { printf(__VA_ARGS__); fprintf(sFile, __VA_ARGS__); } while (0)
extern void vmInit();
extern VmCode *vmLabel(char *label);
extern VmCode *vmCode(char *op, char *d, char *p1, char *p2);
extern VmCode *vmGlobal(char *op, char *d, char *p1, char *p2);
extern void vmDump(VmCode *codes, int top);
extern void vmToAsm(char *file);

#endif