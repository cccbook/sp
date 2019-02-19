#ifndef __MAP_H__
#define __MAP_H__

#include <string.h>
#include <assert.h>
#include <stdio.h>

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

extern Map* mapNew(Map *map, int size);
extern Pair mapAdd(Map *map, char *key, void *value);
extern int mapFind(Map *map, char *key);
extern void* mapLookup(Map *map, char *key);
extern void mapDump(Map *map);

#endif
