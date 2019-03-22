#ifndef __IR_H__
#define __IR_H__

#include <stdio.h>
#include "map.h"
#include "strTable.h"
#include "util.h"

// IR Emit
#define emit printf
extern void irEmitTs(int t, char *s);
extern void irEmitSt(char *s, int t);
extern void irEmitOp2(int t, int p1, char *op, int p2);
extern void irEmitLabel(int label);
extern void irEmitGoto(int label);
extern void irEmitIfGoto(int t, int label);
extern void irEmitIfNotGoto(int t, int label);
extern void irDump();

// IR Virtual Machine
#define trace printf
#define VAR_MAX 10000

typedef struct {
  int t, t1, t2, label;
  char *s, *op;
} IR;


extern IR ir[];
extern int irTop;
extern int L[]; // label => address
extern int irExec(int i);
extern void irRun();
extern void irPrint(IR *p);

#endif
