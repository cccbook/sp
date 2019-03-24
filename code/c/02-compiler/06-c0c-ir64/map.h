#ifndef __MAP_H__
#define __MAP_H__

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef char* string;

typedef struct _Pair {
  char *key;
  void *value;
} Pair;

typedef struct _Map {
  Pair *table;
  int size;
  int top;
} Map;

#define ARRAY_SIZE(list) (sizeof(list)/sizeof(list[0]))
extern unsigned int hash(char *key);
extern Map* mapNew(Map *map, int size);
extern int mapFindIdx(Map *map, char *key);
extern Pair* mapFind(Map *map, char *key);
extern Pair* mapAdd(Map *map, char *key, void *value);
extern void mapAddAll(Map *map, Pair *list, int top);
extern void* mapLookup(Map *map, char *key);
extern void mapDump(Map *map);
extern void mapDumpInt(Map *map);
extern void mapFree(Map *map);

#endif
