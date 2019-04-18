#ifndef __IR_H__
#define __IR_H__

#include <stdio.h>
#include "util.h"

#define emit printf

extern void irEmitTs(int t, char *s);
extern void irEmitSt(char *s, int t);
extern void irEmitOp2(int t, int p1, char *op, int p2);
extern void irEmitLabel(int label);
extern void irEmitGoto(int label);
extern void irEmitIfGoto(int t, int label);
extern void irEmitIfNotGoto(int t, int label);
extern void irDump();

#endif
