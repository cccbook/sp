#ifndef __ASM_H__
#define __ASM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <ctype.h>
#include "../lib/map.h"
#include "../lib/strTable.h"
#include "../lib/util.h"

#define SYM_SIZE 1000
#define S_LEN 20
#define L_LEN 100

typedef struct _Code {
  char type, *label, *a, *c, *d, *j, *line;
  char dtype[S_LEN], *dstr[S_LEN]; // dstr[i] = NULL 就是結束。
  int  size, offset; // , dsize
  uint16_t bin[S_LEN], *bptr[S_LEN];
} Code;

#endif
