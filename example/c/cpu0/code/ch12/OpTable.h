#ifndef OPTABLE_H
#define OPTABLE_H

#include "HashTable.h"

#define OP_LD   0x00
#define OP_ST   0x01
#define OP_LDB  0x02
#define OP_STB  0x03
#define OP_LDR  0x04
#define OP_STR  0x05
#define OP_LBR  0x06
#define OP_SBR  0x07
#define OP_LDI  0x08
#define OP_CMP  0x10
#define OP_MOV  0x12
#define OP_ADD  0x13
#define OP_SUB  0x14
#define OP_MUL  0x15
#define OP_DIV  0x16
#define OP_AND  0x18
#define OP_OR   0x19
#define OP_XOR  0x1A
#define OP_ROL  0x1C
#define OP_ROR  0x1D
#define OP_SHL  0x1E
#define OP_SHR  0x1F
#define OP_JEQ  0x20
#define OP_JNE  0x21
#define OP_JLT  0x22
#define OP_JGT  0x23
#define OP_JLE  0x24
#define OP_JGE  0x25
#define OP_JMP  0x26
#define OP_SWI  0x2A
#define OP_JSUB 0x2B
#define OP_RET  0x2C
#define OP_PUSH 0x30
#define OP_POP  0x31
#define OP_PUSHB 0x32
#define OP_POPB 0x33

#define OP_RESW 0xF0
#define OP_RESB 0xF1
#define OP_WORD 0xF2
#define OP_BYTE 0xF3
#define OP_NULL 0xFF

typedef struct {
  char *name;
  int code;
  char type;
} Op;

void OpTableTest();

HashTable *OpTableNew();
void OpTableFree();

Op* OpNew(char *opLine);
void OpFree(Op *op);
int OpPrintln(Op *op);

extern char *opList[];
extern HashTable *opTable;

#endif
