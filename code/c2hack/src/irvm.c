#include "ir.h"

Pair varList[VAR_MAX];
Map varMap;
int v[VAR_MAX];
int t[VAR_MAX] = { 0 };

int *varLookup(char *name) {
  int h = mapFindIdx(&varMap, name);
  return &v[h];
}

int *varAdd(char *name) {
  return mapAdd(&varMap, name, &t[0])->value;
}

int irOp2(int a, char *op, int b) {
  if (eq(op, "+")) return a + b;
  if (eq(op, "-")) return a - b;
  if (eq(op, "*")) return a * b;
  if (eq(op, "/")) return a / b;
  if (eq(op, "%%")) return a % b;
  if (eq(op, "<")) return a < b;
  if (eq(op, ">")) return a > b;
  if (eq(op, "==")) return a == b;
  if (eq(op, "!=")) return a != b;
  if (eq(op, "<=")) return a <= b;
  if (eq(op, ">=")) return a >= b;
  error("irOp2: op=%s not found!", op);
}

int irExec(int i) {
  IR *p = &ir[i];
  char *op = p->op;
  int pc = i + 1;
  trace("%02d: ", i);
  if (eq(op, "s=t")) {
    int *vp = varLookup(p->s);
    *vp = t[p->t];
    trace("%s = t%d = %d\n", p->s, p->t, *vp);
  } else if (eq(op, "t=s")) {
    int v = (isdigit(*p->s)) ? atoi(p->s) : *varLookup(p->s);
    t[p->t] = v;
    trace("t%d = %s = %d\n", p->t, p->s, v);
  } else if (eq(op, "label")) {
    trace("(L%d) = %d\n", p->label, L[p->label]);
  } else if (eq(op, "goto")) {
    pc = L[p->label];
    trace("goto L%d = %d\n", p->label, pc);
  } else if (eq(op, "if-goto")) {
    int cond = t[p->t];
    trace("if t%d(=%d) ", p->t, cond);
    if (cond) {
      pc = L[p->label];
      trace("goto L%d = %d\n", p->label, pc);
    } else trace(" -- fail\n");
  } else if (eq(op, "ifnot-goto")) {
    int cond = t[p->t];
    trace("ifnot t%d(=%d) ", p->t, cond);
    if (!cond) {
      pc = L[p->label];
      trace("goto L%d = %d\n", p->label, L[p->label]);
    } else trace(" -- fail\n");
  } else {
    t[p->t] = irOp2(t[p->t1], op, t[p->t2]);
    trace("t%d = t%d %s t%d = %d\n", p->t, p->t1, op, p->t2, t[p->t]);
  }
  return pc;
}

void irRun() {
  printf("===================irRun()=======================\n");
  mapNew(&varMap, VAR_MAX);
  for (int pc = 0; pc < irTop;) {
    pc = irExec(pc);
  }
}

