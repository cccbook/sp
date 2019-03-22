#include "ir.h"

typedef struct {
  int t, t1, t2, label;
  char *s, *op;
} IR;

IR ir[TMAX];
int irTop = 0;

void irNew(IR p) {
  ir[irTop++] = p;
}

void irEmitTs(int t, char *s) {
  irNew((IR) {.op="t=s", .t=t, .s=s});
}

void irEmitSt(char *s, int t) {
  irNew((IR) {.op="s=t", .t=t, .s=s});
}

void irEmitOp2(int t, int t1, char *op, int t2) {
  irNew((IR) {.op=op, .t=t, .t1=t1, .t2=t2});
}

void irEmitLabel(int label) {
  irNew((IR) {.op="label", .label=label});
}

void irEmitGoto(int label) {
  irNew((IR) {.op="goto", .label=label});
}

void irEmitIfGoto(int t, int label) {
  irNew((IR) {.op="if-goto", .t=t, .label=label});
}

void irEmitIfNotGoto(int t, int label) {
  irNew((IR) {.op="ifnot-goto", .t=t, .label=label});
}

void irPrint(IR *p) {
  if (eq(p->op, "s=t")) printf("%s = T%d", p->s, p->t);
  else if (eq(p->op, "t=s")) printf("T%d = %s", p->t, p->s);
  else if (eq(p->op, "label")) printf("(L%d)", p->label);
  else if (eq(p->op, "goto")) printf("goto L%d", p->label);
  else if (eq(p->op, "if-goto")) printf("if T%d goto L%d", p->t, p->label);
  else if (eq(p->op, "ifnot-goto")) printf("ifnot T%d goto L%d", p->t, p->label);
  else printf("t%d = t%d %s t%d", p->t, p->t1, p->op, p->t2);
  printf("\n");
}

void irDump() {
  for (int i=0; i<irTop; i++) {
    irPrint(&ir[i]);
  }
}
/*
int irExec(IR p) {
  if (eq(p->op, "s=t")) printf("%s = T%d", p->s, p->t);
  else if (eq(p->op, "t=s")) printf("T%d = %s", p->t, p->s);
  else if (eq(p->op, "label")) printf("(L%d)", p->label);
  else if (eq(p->op, "goto")) printf("goto L%d", p->label);
  else if (eq(p->op, "if-goto")) printf("if T%d goto L%d", p->t, p->label);
  else if (eq(p->op, "ifnot-goto")) printf("ifnot T%d goto L%d", p->t, p->label);
  else printf("t%d = t%d %s t%d", p->t, p->t1, p->op, p->t2);
  printf("\n");
}

void irRun() {
  int pc = 0;
  for (int i=0; i<irTop; i++) {
    pc = irExec(&ir[i]);
  }
}

*/