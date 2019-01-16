#include "map.h"

unsigned int hash(char *key) {
  char *p = key;
  unsigned int  h = 3;
  while (*p != '\0') {
    h = h * 147 + *p++;
  }
  return h;
}

Map* mapNew(Map *map, Pair *list, int size, int top) {
  map->list = list;
  map->size = size;
  map->top = top;
  return map;
}

Pair mapAdd(Map *map, char *key, void *value) {
  assert(map->top < map->size);
  Pair p = { key, value };
  map->list[map->top++] = p;
  return p;
}

int mapFind(Map *map, char *key) {
  for (int i=0; i<map->top; i++) {
    if (strcmp(map->list[i].key, key)==0)
      return i;
  }
  return -1;
}

void* mapLookup(Map *map, char *key) {
  int i = mapFind(map, key);
  if (i==-1) return NULL;
  return map->list[i].value;
}

void mapDump(Map *map) {
  printf("======= mapDump() ==============\n");
  for (int i=0; i<map->top; i++) {
    Pair *p = &map->list[i];
    printf("  %s %s\n", p->key, (char*) p->value);
  }
}
