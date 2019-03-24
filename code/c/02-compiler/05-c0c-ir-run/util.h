#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TMAX 100000
#define SMAX 100

#define eq(x,y) (strcmp((x),(y))==0)
#define error(...) ({ printf(__VA_ARGS__); assert(0); })

extern int readText(char *fileName, char *text, int size);

#endif