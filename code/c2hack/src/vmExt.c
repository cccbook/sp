#include "vm.h"

float   *F = (float*) &m[24577];

int putstr(int16_t *str) {
  int16_t *p = str;
  while (*p != 0) {
    printf("%c", (char) *p++);
  }
  return p-str;
}

// 一開始就載入 im 到 m，所以不需要再有 D=I 之類的指令了。
void swi(int16_t A, int16_t D) {
  switch (A) {
    case 0x00: // swi 0: print integer
      printf("%d", D);
      break;
    case 0x01: // swi 1: print char
      printf("%c", (char) D);
      break;
    case 0x03: // swi 3: print string in m
      putstr(&m[D]);
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

// C 型指令的擴充指令集 aluExt
int aluExt(int16_t c, int16_t A, int16_t D, int16_t AM) {
  int16_t out = 0;
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
