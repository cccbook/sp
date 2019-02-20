#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SMAX 256            // 短字串最大長度
#define TMAX (1024*1024)    // 長字串最大長度
extern int readText(char *fileName, char *text, int size);
extern int isMember(char *token, char *set);
#define MAX(a,b) (((a)>(b)) ? (a) : (b))

#endif
