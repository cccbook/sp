#include "hack.h"

void ir2macro(FILE *fp, IR *p) {
  int t=p->t, t1=p->t1, t2=p->t2, label=p->label;
  char *s = p->s, AM;
  // fprintf(fp, "// "); irWrite(stdout, p);
  switch (p->type) {
    // case IrCall: error("IrCall"); break;
    // case IrArg:  error("IrArg"); break;
    case IrAssignSt:
      AM = isdigit(*s) ? 'A' : 'M';
      fprintf(fp, "@t%d\nD=%c\n@%s\nM=D", t, AM, s); // s=t
      break;
    case IrAssignTs:
      fprintf(fp, "@%s\nD=M\n@t%d\nM=D", s, t); // t=s
      break;
    case IrLabel: // (label)
      fprintf(fp, "(L%d)", p->label);
      break;
    case IrGoto: // goto label
      fprintf(fp, "@L%d\n0;JMP", p->label);
      break;
    case IrIfGoto: // if t goto label
      fprintf(fp, "@t%d\nD=M\n@L%d\nD;JEQ", p->t, p->label);
      break;
    case IrIfNotGoto: // ifnot t goto label
      fprintf(fp, "@t%d\nD=M\n@L%d\nD;JNE", p->t, p->label);
      break;
    case IrOp2: // t = t1 op t2
      fprintf(fp, "@t%d\nD=M\n@t%d\nD=D%sM\n@t%d\nM=D", p->t1, p->t2, p->op, p->t);
      break;
    default: 
      error("ir.type %d not found!", p->type);
  }
  printf("\n");
}

void ir2m0(char *m0File) {
  FILE *m0F = fopen(m0File, "w");
  for (int i=0; i<irTop; i++) {
    ir2asm1(m0F, &ir[i]);
  }
  fclose(m0F);
}