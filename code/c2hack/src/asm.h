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

#define SYM_SIZE 1000
#define S_LEN 20
#define L_LEN 100

typedef struct _Code {
  int size;
  char type, label[S_LEN], a[S_LEN], c[S_LEN], d[S_LEN], j[S_LEN], str[L_LEN];
} Code;

#endif
