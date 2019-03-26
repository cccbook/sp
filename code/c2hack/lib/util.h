#ifndef __UTIL_H__
#define __UTIL_H__

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdarg.h>

extern int readText(char *fileName, char *text, int size);
extern void argHandle(int argc, char *argv[], int argMin, char *msg);
extern void hexDump16(uint16_t *words, int len);
extern int  error(char *msg);
extern void replace(char *str, char *set, char t);
extern void htob(char* hex, char* binary);
extern void itob(int i, char* binary);
extern int  btoi(char* binary);
extern void format(char *buf, char *fmt, ...);

#define NMAX 20
#define SMAX 100
#define TMAX 1000

#define member(c, set) strchr(set, c)
#define error(...) { printf(__VA_ARGS__); assert(0); }
#define eq(x,y) (strcmp((x),(y))==0)
#define debug(...) { if (isDebug) printf(__VA_ARGS__); }


extern char isDebug;
extern char isFlag[];

#endif
