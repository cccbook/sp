#include <stdio.h>
#include <assert.h>
#include <stdint.h>

int16_t D = 0, A = 0, PC = 0;
uint16_t I = 0;
int16_t im[32768], m[24576+5];
int16_t *Keyboard = &m[24576];
float   *F = (float*) &m[24577];

#define BIT0 0x0001
#define BIT1 0x0002
#define BIT2 0x0004

int cAssignExt(int16_t c, int16_t D, int16_t AM);

int error(char *msg) {
  printf("Error: %s", msg);
  assert(0);
}

// C 型指令的 cTable 之處理, 也就是T = X op Y 的狀況 
int cAssign(int16_t c, int16_t D, int16_t AM) {
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
    default: out = cAssignExt(c, D, AM); // 擴充指令集
  }
  return out;
}

// C 型指令的擴充指令集 aluExt
int cAssignExt(int16_t c, int16_t D, int16_t AM) {
  int16_t out = 0;
  char msg[100];
  switch (c) {
    case 0x20: out = D << AM;  break; // 左移
    case 0x21: out = D >> AM;  break; // 右移
    case 0x22: out = D * AM;   break; // 乘法
    case 0x23: out = D / AM;   break; // 除法
    case 0x24: out = D % AM;   break; // 餘數
    case 0x25: out = D < AM;   break; // 小於
    case 0x26: out = D <= AM;  break; // 小於或等於
    case 0x27: out = D > AM;   break; // 大於
    case 0x28: out = D >= AM;  break; // 大於或等於
    case 0x29: out = D == AM;  break; // 等於
    case 0x2B: out = D != AM;  break; // 不等於
    case 0x2C: out = D ^ AM;   break; // xor
    default:
      sprintf(msg, "HackAlu + HackAluExt do not support c=0x%x\n", c);
      error(msg);
  }
  return out;
}

// 處理 C 型指令
int cInstr(int16_t i, int16_t a, int16_t c, int16_t d, int16_t j) {
  int AM = (a == 0) ? A : 
           (i == 0) ? im[A] : m[A];
  int16_t aluOut = cAssign(c, D, AM);
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
/*
int ioInstr(int16_t e, int16_t a, int16_t c, int16_t d, int16_t j) {
  swtich (c)
    case 0x2E: printf("%d", (char) D); break; // outi: 輸出 AM 所代表的數值
    case 0x2F: printf("%c", (char) D); break; // outc: 輸出 AM 所代表的字元
}
*/
// 模擬浮點協同處理器 hackFpu
int fInstr(int16_t c, float *F) { // F 指向浮點數的記憶體映射暫存器
  float f0 = F[0], f1=F[1];
  switch (c) {
    case 0x02: f0 = f0 + f1; break;    // 浮點加法
    case 0x03: f0 = f0 -  f1; break;   // 浮點減法
    case 0x04: f0 = f0 *  f1; break;   // 浮點乘法
    case 0x05: f0 = f0 /  f1; break;   // 浮點除法
    case 0x06: f0 = f0 <  f1; break;   // 小於
    case 0x07: f0 = f0 <= f1; break;   // 小於或等於
    case 0x08: f0 = f0 >  f1; break;   // 大於
    case 0x09: f0 = f0 >= f1; break;   // 大於或等於
    case 0x0A: f0 = f0 == f1; break;   // 等於
    case 0x0B: f0 = f0 != f1; break;   // 不等於
    default: assert(0);
  }
  F[0] = f0; F[1] = f1;
}

// 虛擬機主程式
int run(uint16_t *im, int16_t *m, int imTop) {
  char msg[100];
  uint16_t f, i, a, c, d, j, e;
  while (1) {
    printf("imTop=%d PC=%d\n", imTop, PC);
    if (PC >= imTop) { 
      printf("exit program !\n");
      break;
    }
    I = im[PC];
    printf("PC=%04X I=%04X", PC, I);
    PC ++;
    if ((I & 0x8000) == 0) { // A 指令
      A = I;
    } else { // C 指令
      f = (I & 0x4000) >> 14; // f=1 使用 FPU, f=0 使用 CPU
      i = (I & 0x2000) >> 13; // i=1 存取指令記憶體 IM，i=0 存取資料記憶體 M, 
      a = (I & 0x1000) >> 12;
      c = (I & 0x0FC0) >>  6;
      d = (I & 0x0038) >>  3;
      j = (I & 0x0007) >>  0;
      if (f)
        cInstr(i, a, c, d, j);
      else 
        fInstr(c, F);
    }
    printf(" A=%04hX D=%04hX=%05d m[A]=%04hX", A, D, D, m[A]);
    if ((I & 0x8000) != 0) printf(" a=%X c=%02X d=%X j=%X", a, c, d, j);
    printf("\n");
  }
}

// run: ./vm <file.bin>
int main(int argc, char *argv[]) {
  char *binFileName = argv[1];
  FILE *binFile = fopen(binFileName, "rb");
  int imTop = fread(im, sizeof(uint16_t), 32768, binFile);
  fclose(binFile);
  run(im, m, imTop);
}
