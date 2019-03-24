#ifndef __ASM_H__
#define __ASM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <ctype.h>
#include "map.h"
#include "strTable.h"
#include "util.h"
#include "objFile.h"

#define SYM_SIZE 1000
#define S_LEN 20
#define L_LEN 100

typedef struct {
  char type;
  char *token;
  uint16_t offset;
} Data;

typedef struct _Code {
  char type, *label, *a, *c, *d, *j, line[SMAX], src[SMAX];
  Data data[SMAX];
  int  size, offset;
  uint16_t bin[SMAX];
} Code;

#endif
