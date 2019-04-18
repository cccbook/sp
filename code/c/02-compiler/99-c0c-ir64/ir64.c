#include "ir64.h"

#define R_PC   0xF0 // Program Counter
#define R_SP   0xF1 // Stack Pointer
#define R_FP   0xF2 // Frame Pointer
#define R_LR   0xF3 // Link Register
#define R_DS   0xF4 // Data Segment
#define R_CS   0xF5 // Code Segment
#define R_N1   0xFF // R[FF] is always -1 = 0xFFFFFFFFFF
#define R_C0   0x00 // R[0]  is always  0 = 0x0000000000

char *Rname[16] = {
  "pc", "sp", "fp", "lr", "ds", "cs", "rf6", "rf7", "rf8", "rf9", "rfa", "rfb", "rfc", "rfd", "n1"
};

void rname(int r, char *name) {
  if (r >= 0xF0) sprintf(name, "%s", Rname[r-0xF0]); else sprintf(name, "r%x", r);
}

#define OP_TOP 64

char *opName[OP_TOP] = {
//    0      1      2      3      4      5      6      7     8     9     A     B     C     D     E     F
/*0*/ "",    "+",   "-",   "*",   "/",   "%%",  "&",   "|",   "^",  "<<", ">>", "",   "",   "",   "",   "",   
/*1*/ "<",   ">",   "<=",  ">=",  "==",  "!=",  "&&",  "||", "",   "",   "",   "",   "",   "",   "",   "",
/*2*/ "ld1", "ld2", "ld3", "ld4", "ld5", "ld6", "ld7", "ld8","st1","st2","st3","st4","st5","st6","st7","st8",
/*3*/ "jlt", "jgt", "jle", "jge", "jeq", "jne", "jmp", "",   "",   "",   "",   "",   "",   "",   "",   "",
};

typedef enum {
// 0           1         2       3       4       5       6        7       8        9       A       B       C       D       E       F
               OP_ADD=1, OP_SUB, OP_MUL, OP_DIV, OP_MOD, OP_BAND, OP_BOR, OP_BXOR, OP_SHL, OP_SHR, 
  OP_LT =0x10, OP_GT,    OP_LE,  OP_GE,  OP_EQ,  OP_NE,  OP_LAND, OP_LOR, 
  OP_LD1=0x20, OP_LD2,   OP_LD3, OP_LD4, OP_LD5, OP_LD6, OP_LD7,  OP_LD8, OP_ST1,  OP_ST2, OP_ST3, OP_ST4, OP_ST5, OP_ST6, OP_ST7, OP_ST8,
  OP_JLT=0x30, OP_JGT, OP_JLE, OP_JGE, OP_JEQ, OP_JNE, OP_JMP,  
} OpCode;

int opCode[OP_TOP];

//                      0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F 
#define OP_B 0x0F // 0: +   -   *   /   %   &   |   ^   <<  >> 
#define OP_C 0x1F // 1: <   >   <=  >=  ==  !=  &&  ||
#define OP_M 0x2F // 2: ld1 ld2 ld4 ld8 st1 st2 st4 st8
#define OP_J 0x3F // 3: jlt jgt jle jge jeq jne jmp

IR64 ir64[IR_MAX];
int64_t ir64label[IR_MAX];
int64_t ir64top = 0;

#define M_TOP 10000
#define R_TOP 255

int64_t R[R_TOP];
int64_t M[M_TOP];

Map opMap;

int opMapInit() {
  mapNew(&opMap, 549);
  for (int i=0; i<OP_TOP; i++) {
    opCode[i] = i;
    if (opName[i] && !eq(opName[i], "")) {
      mapAdd(&opMap, opName[i], &opCode[i]);
    }
  }
}

int op2i(char *op) {
  int *ip = mapLookup(&opMap, op);
  assert(ip != NULL);
  return *ip;
}

int symTop = 0;
Map symMap;

typedef struct {
  int idx, addr;
  char type; // G:Global, B:label, A:arg, C:local
} Symbol;

Symbol symList[VAR_MAX];
int globalTop = 0;
int L[VAR_MAX];

int *symLookup(char *name) {
  int *vp = mapLookup(&symMap, name);
  return vp;
}

int *symAdd(char *name, char type, int addr) {
  Symbol s = {.type = type, .addr=addr, .idx=symTop };
  symList[symTop++] = s;
  return mapAdd(&symMap, name, &symList[symTop++])->value;
}

// ============================= IR64 ====================================

void ir64init() {
  opMapInit();
  mapNew(&symMap, VAR_MAX);
  // mapDumpInt(&opMap);
  ir64top = 0;
}

void ir64print(int i, IR64 *r) {
  int m = r->m, op = r->op, r0 = r->r0, r1 = r->r1, r2 = r->r2, c = r->c;
  if (op & 0x20) { // ex: ld8, jgt ...
    char r1name[20], r2name[20]; 
    rname(r1, r1name);
    if (r1 == 0) r1name[0] = '\0';
    if (r2 == 0) sprintf(r2name, ""); else sprintf(r2name, "+r%x", r2);
    if (m) {
      printf("%02d: %s r%x [%s%s%+d]\n", i, opName[op], r0, r1name, r2name, c);
    } else {
      printf("%02d: %s r%x %s%s%+d\n", i, opName[op], r0, r1name, r2name, c);
    }
  } else {
    printf("%02d: r%d = r%d%sr%d\n", i, r0, r1, opName[op], r2);
  }
}

void ir64pass1(IR *r) {
  assert(r->t < 254 && r->t1 < 254 && r->t2 < 254); // 因為 ir64 只有 253 個可用暫存器，temp 代號不能超過暫存器數量！
  IR64 r64;
  memset(&r64, 0, sizeof(r64));
  if (r->s) {
    if (isdigit(*r->s)) {
        r64.m = 0; // no memory access
        r64.c = atoi(r->s);
    } else {
      r64.m = 1; // memory access
      int *sp = symLookup(r->s);
      // printf("ir64jit1: vip=%p\n", vip);
      if (!sp) sp = symAdd(r->s, 'G', globalTop);
      r64.c = globalTop++;
      r64.r1 = R_DS;
    }
  }
  switch (r->type) {
    case IrAssignTs: r64.op = op2i("ld8"); r64.r0 = r->t; break;
    case IrAssignSt: r64.op = op2i("st8"); r64.r0 = r->t; break;
    case IrOp2: // ex: + r3, r1, r2   ==>   r3 = r1 op r2
      r64.op = op2i(r->op);
      r64.r0 = r->t; r64.r1 = r->t1; r64.r2 = r->t2; 
      break;
    case IrLabel:
      L[r->label] = ir64top;
      printf("%02d: (L%d)\n", ir64top, r->label);
      return;
    // case IrCall1:
    case IrGoto:
    case IrIfGoto:
    case IrIfNotGoto: 
      ir64label[ir64top] = r->label;
      printf("pass2 : label= %d >> ", r->label);
      r64.r0 = r->t;
      if (r->type == IrGoto) r64.op = op2i("jmp");
      else if (r->type == IrIfGoto) r64.op = op2i("jeq"); 
      else if (r->type == IrIfNotGoto) r64.op = op2i("jne"); 
      break;
    // case IrCall:
    // case IrArg:
  }

  ir64print(ir64top, &r64);
  ir64[ir64top++] = r64;
}

void ir64pass2(IR64 *r64, int label, int i) {
  if ((r64->op & 0x30) == 0x30) {
    assert(label != 0);
    r64->r1 = R_CS;
    r64->c  = L[label]; 
  }
  ir64print(i, r64);
}

void ir64jit() {
  symTop = 0;
  printf("============pass1=========\n");
  for (int i=0; i<irTop; i++) {
    ir64pass1(&ir[i]);
  }
  printf("============pass2=========\n");
  for (int i=0; i<ir64top; i++) {
    ir64pass2(&ir64[i], ir64label[i], i);
  }
}

void ir64dump() {
  printf("========ir64dump()=========\n");
  for (int i=0; i<ir64top; i++) {
    ir64print(i, &ir64[i]);
  }
}

--xxx; // 這裡要預留設定 DS，CS 的空間 (啟動程式)，乾脆預留整個 Boot 好了！。

int ir64exec(int i) {
  IR *r = &ir64[i];
  OpCode op = r->op;
  int64_t r0 = r->r0, r1=r->r1, r2=r->r2, c = r->c, m = r->m;
  int64_t R0 = R[r0], R1 = R[r1], R2 = R[r2];
  int64_t R12c = R1+R2+c;
  ir64print(i, r);

  int64_t pc = i + 1;
  switch (op) {
    case OP_LD8: R[r0] = M[R12c]; break;
    case OP_ST8: M[R12c] = R[r0]; break;
    case OP_JMP: R[R_PC] = R12c; break;
    case OP_JLT: if (R0 < 0)  pc = R12c; break;
    case OP_JGT: if (R0 > 0)  pc = R12c; break;
    case OP_JLE: if (R0 <= 0) pc = R12c; break;
    case OP_JGE: if (R0 >= 0) pc = R12c; break;
    case OP_JEQ: if (R0 == 0) pc = R12c; break;
    case OP_JNE: if (R0 != 0) pc = R12c; break;
    case OP_ADD: R[r0] = R1 +  R2; break;
    case OP_SUB: R[r0] = R1 -  R2; break;
    case OP_MUL: R[r0] = R1 *  R2; break;
    case OP_DIV: R[r0] = R1 /  R2; break;
    case OP_MOD: R[r0] = R1 %  R2; break;
    case OP_SHL: R[r0] = R1 << c; break;
    case OP_SHR: R[r0] = R1 >> c; break;
    case OP_BAND:R[r0] = R1 &  R2; break;
    case OP_BOR: R[r0] = R1 |  R2; break;
    case OP_BXOR:R[r0] = R1 ^  R2; break;
    case OP_LT:  R[r0] = R1 <  R2; break;
    case OP_LE:  R[r0] = R1 <= R2; break;
    case OP_GT:  R[r0] = R1 >  R2; break;
    case OP_GE:  R[r0] = R1 >= R2; break;
    case OP_EQ:  R[r0] = R1 == R2; break;
    case OP_NE:  R[r0] = R1 != R2; break;
    case OP_LAND:R[r0] = R1 &  R2; break;
    case OP_LOR: R[r0] = R1 |  R2; break;
    default: error("ir64exec : op=%02x not found!", op);
  }
  return pc;
}

void ir64run() {
  printf("===================ir64run()=======================\n");
  for (int16_t pc = 0; pc < ir64top;) {
    pc = ir64exec(pc);
  }
}


/*
int ir64op2(int a, OpCode op, int b) {
  switch (op) {
    case OP_ADD: return a + b;
    case OP_SUB: return a - b;
    case OP_MUL: return a * b;
    case OP_DIV: return a / b;
    case OP_MOD: return a % b;
    case OP_BAND: return a & b;
    case OP_BOR: return a | b;
    case OP_BXOR: return a ^ b;
    case OP_SHL: return a << b;
    case OP_SHR: return a >> b;
    case OP_LT: return a < b;
    case OP_GT: return a > b;
    case OP_LE: return a <= b;
    case OP_GE: return a >= b;
    case OP_EQ: return a == b;
    case OP_NE: return a != b;
    case OP_LAND: return a && b;
    case OP_LOR: return a || b;
    default: error('ir64op2: op=%02x not found!', op);
  }
}
*/
