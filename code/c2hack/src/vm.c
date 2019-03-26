#include "vm.h"

int16_t D = 0, A = 0, PC = 0;
uint16_t I = 0;
uint16_t im[32768];
int16_t m[24576+5];
int16_t *Keyboard = &m[24576];

// ALU: C 型指令的 cTable 之處理, 也就是T = X op Y 的狀況 
int alu(int16_t c, int16_t A, int16_t D, int16_t AM) {
  int16_t out = 0;
  switch (c) {
    case 0x00: out = D&AM; break; // "D&AM","000000"
    case 0x02: out = D+AM; break; // "D+AM","000010"
    case 0x07: out = AM-D; break; // "AM-D","000111"
    case 0x0C: out = D;  break;   // "D",   "001100"
    case 0x0D: out = D^0xFFFF; break; // "!D",  "001101"
    case 0x0E: out = D-1; break; // "D-1", "001110"
    case 0x0F: out = -D; break;   // "-D",  "001111"
    case 0x13: out = D-AM; break; // "D-AM","010011"
    case 0x15: out = D|AM; break; // "D|AM","010101"
    case 0x1F: out = D+1; break;  // "D+1", "011111"
    case 0x2A: out = 0;  break;   // "0",   "101010"
    case 0x30: out = AM; break;   // "AM",  "110000"
    case 0x31: out = AM^0xFFFF; break; // "!AM", "110001"
    case 0x32: out = AM-1; break; // "AM-1","110010"
    case 0x33: out = -AM; break;  // "-AM", "110011"
    case 0x37: out = AM+1; break; // "AM+1","110111"
    case 0x3A: out = -1; break;   // "-1",  "111010"
    case 0x3F: out = 1;  break;   // "1",   "111111"
#ifdef _VM_EXT_
    default: out = aluExt(c, A, D, AM); // 擴充指令集
#else
    default: error("alu: c=%d not found!", c);
#endif
  }
  return out;
}

// 處理 C 型指令
void cInstr(int16_t a, int16_t c, int16_t d, int16_t j) { // int16_t i, 
  int AM = (a == 0) ? A : m[A];
  int16_t aluOut = alu(c, A, D, AM);
  if (d&BIT2) A = aluOut;
  if (d&BIT1) D = aluOut;
  if (d&BIT0) m[A] = aluOut;
  switch (j) {
    case 0x0: break;                          // 不跳躍
    case 0x1: if (aluOut >  0) PC = A; break; // JGT
    case 0x2: if (aluOut == 0) PC = A; break; // JEQ
    case 0x3: if (aluOut >= 0) PC = A; break; // JGE
    case 0x4: if (aluOut <  0) PC = A; break; // JLT
    case 0x5: if (aluOut != 0) PC = A; break; // JNE
    case 0x6: if (aluOut <= 0) PC = A; break; // JLE
    case 0x7: PC = A; break;                  // JMP
  }
}

// HackCPU : 
void cpu(uint16_t I) {
  uint16_t a, c, d, j;
  debug("PC=%04X I=%04X", PC, I);
  PC ++;
  if ((I & 0x8000) == 0) { // A 指令
    A = I;
  } else { // C 指令
    a = (I & 0x1000) >> 12;
    c = (I & 0x0FC0) >>  6;
    d = (I & 0x0038) >>  3;
    j = (I & 0x0007) >>  0;
    cInstr(a, c, d, j);
  }
  debug(" A=%04hX D=%04hX=%05d m[A]=%04hX", A, D, D, m[A]);
  if (I & 0x8000) debug(" a=%X c=%02X d=%X j=%X", a, c, d, j);
  debug("\n");
}

// 虛擬機主程式
void run(uint16_t *im, int16_t *m, int imTop) {
  while (1) {
    if (PC >= imTop) break; // 超出範圍，虛擬機自動結束。
    I = im[PC];
    cpu(I);
  }
}

// run: ./vm <file.bin>
int main(int argc, char *argv[]) {
  argHandle(argc, argv, 2, "./vm <file.bin>\n");

  FILE *binFile = fopen(argv[1], "rb");
  int imTop = fread(im, sizeof(uint16_t), 32768, binFile);
  if (isDebug) { hexDump16(im, imTop); debug("\n"); }
  fclose(binFile);

  memcpy(m, im, imTop); // 啟動後將指令記憶體 im 複製到資料記憶體 m，這樣就不需要存取 im 的指令了。
  run(im, m, imTop);
  return 0;
}
