#ifndef __UTIL_H__
#define __UTIL_H__

#include <string.h>
#include <stdio.h>
#include <assert.h>

extern void htob(char* hex, char* binary);
extern void itob(int i, char* binary);
extern int btoi(char* binary);

#endif
