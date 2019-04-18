#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include "../lib/util.h"

int16_t D = 0, A = 0, PC = 0;
uint16_t I = 0;
uint16_t im[32768];
int16_t m[24576+5];
int16_t *Keyboard = &m[24576];
float   *F = (float*) &m[24577];

#define BIT0 0x0001
#define BIT1 0x0002
#define BIT2 0x0004

int aluExt(int16_t c, int16_t A, int16_t D, int16_t AM);
void swi(int16_t A, int16_t D);

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
    default: out = aluExt(c, A, D, AM); // 擴充指令集
  }
  return out;
}

// C 型指令的擴充指令集 aluExt
int aluExt(int16_t c, int16_t A, int16_t D, int16_t AM) {
  int16_t out = 0; // , *mp;
  // char *p, line[100], msg[100];
  switch (c) {
    // 運算延伸指令 : 使用 10xxxx ，避開 {"0",   "101010"}
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
    case 0x2D: error("call not defined!"); break; // {"call", "101101"},
    case 0x2E: error("ret not defined!"); break;  // {"ret",  "101110"},
    case 0x2F: swi(A, D); break;
    default: break;
  }
  return out;
}

int putstr(int16_t *str) {
  int16_t *p = str;
  while (*p != 0) {
    printf("%c", (char) *p++);
  }
  return p-str;
}

// 一開始就載入 im 到 m，所以不需要再有 D=I 之類的指令了。
void swi(int16_t A, int16_t D) {
  // float f;
  switch (A) {
    case 0x00: // swi 0: print integer
      printf("%d", D);
      break;
    case 0x01: // swi 1: print char
      printf("%c", (char) D);
      break;
    case 0x02:
      error("swi: A=0x02 reserved!");
      break;
    case 0x03: // swi 3: print string in m
      putstr(&m[D]);
      break;
    case 0x04: // swi 4: print float in im
      error("swi: A=0x02 reserved!"); // putstr(&im[D]);
      break;
    case 0x10: // swi 16: fseti
      error("swi: A=0x10 reserved!"); // *F = *(float*) &im[D];
      break;
    case 0x11: // swi 17: fsetm
      *F = *(float*) &m[D];
      break;
    case 0x12: // swi 18: fput
      printf("%f ", *F);
      break;
    case 0x13: // swi 19: fadd
      *F += *(float*) &m[D];
      break;
    case 0x14: // swi 20: fsub
      *F -= *(float*) &m[D];
      break;
    case 0x15: // swi 21: fmul
      *F *= *(float*) &m[D];
      break;
    case 0x16: // swi 22: fdiv
      *F /= *(float*) &m[D];
      break;
  }
}


// 處理 C 型指令
void cInstr(int16_t i, int16_t a, int16_t c, int16_t d, int16_t j) {
  assert(i==1);
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

void ioInstr(int16_t c) {
  error("目前不支援 ioInstr() 指令");
}

// 虛擬機主程式
void run(uint16_t *im, int16_t *m, int imTop) {
  // char msg[100];
  uint16_t p, i, a, c, d, j; // , e;
  while (1) {
    if (PC >= imTop) break; // 超出範圍，虛擬機自動結束。
    I = im[PC];
    debug("PC=%04X I=%04X", PC, I);
    PC ++;
    if ((I & 0x8000) == 0) { // A 指令
      A = I;
    } else { // C 指令
      p = (I & 0x4000) >> 14; // p=1 使用 CPU，p=0 使用外掛裝置 (例如 IO，FPU)
      i = (I & 0x2000) >> 13; // i=1 存取指令記憶體 IM，i=0 存取資料記憶體 M, 
      a = (I & 0x1000) >> 12;
      c = (I & 0x0FC0) >>  6;
      d = (I & 0x0038) >>  3;
      j = (I & 0x0007) >>  0;
      if (p)
        cInstr(i, a, c, d, j);
      else
        ioInstr(c);
    }
    debug(" A=%04hX D=%04hX=%05d m[A]=%04hX", A, D, D, m[A]);
    if (I & 0x8000) debug(" a=%X c=%02X d=%X j=%X", a, c, d, j);
    debug("\n");
  }
}

// run: ./vm <file.bin>
int main(int argc, char *argv[]) {
  argHandle(argc, argv, 2, "./vm <file.bin>\n");

  FILE *binFile = fopen(argv[1], "rb");
  int imTop = fread(im, sizeof(uint16_t), 32768, binFile);
  if (isDebug) { hexDump16(im, imTop); printf("\n"); }
  fclose(binFile);

  memcpy(m, im, imTop); // 啟動後將指令記憶體 im 複製到資料記憶體 m，這樣就不需要存取 im 的指令了。
  run(im, m, imTop);
  return 0;
}
