#include "hack.h"

void ir2asm1(IR *p) {
  int t=p->t, t1=p->t1, t2=p->t2, label=p->label;
  char *s = p->s, AM;
  emit("// "); irPrint(p);
  switch (p->type) {
    // case IrCall: error("IrCall"); break;
    // case IrArg:  error("IrArg"); break;
    case IrAssignSt:
      AM = isdigit(*s) ? 'A' : 'M';
      emit("@t%d\nD=%c\n@%s\nM=D", t, AM, s); // s=t
      break;
    case IrAssignTs:
      emit("@%s\nD=M\n@t%d\nM=D", s, t); // t=s
      break;
    case IrLabel: // (label)
      emit("(L%d)", p->label);
      break;
    case IrGoto: // goto label
      emit("@L%d\n0;JMP", p->label);
      break;
    case IrIfGoto: // if t goto label
      emit("@t%d\nD=M\n@L%d\nD;JEQ", p->t, p->label);
      break;
    case IrIfNotGoto: // ifnot t goto label
      emit("@t%d\nD=M\n@L%d\nD;JNE", p->t, p->label);
      break;
    case IrOp2: // t = t1 op t2
      emit("@t%d\nD=M\n@t%d\nD=D%sM\n@t%d\nM=D", p->t1, p->t2, p->op, p->t);
      break;
    default: 
      error("ir.type %d not found!", p->type);
  }
  printf("\n");
}

void ir2asm() {
  for (int i=0; i<irTop; i++) {
    ir2asm1(&ir[i]);
  }
}