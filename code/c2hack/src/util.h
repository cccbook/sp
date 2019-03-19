#ifndef __UTIL_H__
#define __UTIL_H__

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

extern void hexDump16(uint16_t *words, int len, char *hex);
extern int  error(char *msg);
extern void replace(char *str, char *set, char t);
extern void htob(char* hex, char* binary);
extern void itob(int i, char* binary);
extern int  btoi(char* binary);

#define NMAX 20
#define SMAX 100
#define TMAX 1000

#define member(c, set) strchr(set, c)
#define error(...) ({ printf(__VA_ARGS__); assert(0); })


#endif
