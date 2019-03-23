#ifndef __IR64_H__
#define __IR64_H__

#include <stdint.h>
#include "ir.h"

typedef struct {
  int32_t c  : 32;
  uint8_t x  : 1;
  uint8_t m  : 1;
  uint8_t op : 6;
  uint8_t r0 : 8;
  uint8_t r1 : 8;
  uint8_t r2 : 8;
} IR64;

extern void ir64init();
extern void ir64jit();
extern void ir64run();
extern void ir64dump();

#endif