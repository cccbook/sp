#ifndef CPU0_H
#define CPU0_H

#include "OpTable.h"

typedef struct {
  BYTE *m;
  int mSize;
  int R[16], IR;
} Cpu0;

void runObjFile(char *objFile); // 虛擬機器的主要函數 

Cpu0* Cpu0New(char *objFile);
void Cpu0Free(Cpu0 *cpu0);
void Cpu0Run(Cpu0 *cpu0, int startPC);
void Cpu0Dump(Cpu0 *cpu0);

#endif
