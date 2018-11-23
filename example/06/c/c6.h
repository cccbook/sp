#ifndef __C6__
#define __C6__

#include <string.h>

typedef char* string;

#define c6size(array) (sizeof(array)/sizeof(array[0]))

typedef struct _Pair {
  char *key;
  void *value;
} Pair;

typedef struct _Map {
  Pair *list;
  int size;
  int top;
} Map;

typedef struct _StrTable {
  char *text;
  int size;
  char *textEnd;
} StrTable;

extern Map *c6mapNew(Map *map, Pair *list, int size);
extern Pair c6mapAdd(Map *map, char *key, void *value);
extern int c6mapFind(Map *map, char *key);
extern void *c6mapLookup(Map *map, char *key);
extern void c6htob(string hex, string binary);
extern void c6itob(int i, string binary);
extern int c6btoi(string binary);
extern void c6strTable(StrTable *t, char *text, int size);
extern char *c6strNew(StrTable *t, char *str);
#endif
