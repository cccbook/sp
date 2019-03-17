#ifndef __UTIL_H__
#define __UTIL_H__

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

extern void hexDump16(uint16_t *words, int len);
extern int  error(char *msg);
extern void replace(char *str, char *set, char t);
extern void htob(char* hex, char* binary);
extern void itob(int i, char* binary);
extern int  btoi(char* binary);

#define member(c, set) strchr(set, c)

#endif
