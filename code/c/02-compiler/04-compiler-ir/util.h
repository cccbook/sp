#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TMAX 100000
#define SMAX 100

#define isDigit(ch) ((ch) >= '0' && (ch) <='9')
#define isAlpha(ch) (((ch) >= 'a' && (ch) <='z') || ((ch) >= 'A' && (ch) <= 'Z'))
#define eq(x,y) (strcmp((x),(y))==0)

#endif