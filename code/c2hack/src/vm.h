#ifndef __VM_H__
#define __VM_H__

#include "../lib/util.h"

#define BIT0 0x0001
#define BIT1 0x0002
#define BIT2 0x0004

extern int16_t m[];

#ifdef _VM_EXT_
int aluExt(int16_t c, int16_t A, int16_t D, int16_t AM);
#endif

#endif
