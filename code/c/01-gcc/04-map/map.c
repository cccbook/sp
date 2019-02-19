#include "map.h"

Map* mapNew(Map *map, int size) {
  map->table = NULL;
  map->size = size;
  map->top = 0;
  return map;
}

Pair mapAdd(Map *map, char *key, void *value) {
  assert(map->top < map->size);
  Pair p = { key, value };
  map->table[map->top++] = p;
  return p;
}

int mapFind(Map *map, char *key) {
  for (int i=0; i<map->top; i++) {
    if (strcmp(map->table[i].key, key)==0)
      return i;
  }
  return -1;
}

void* mapLookup(Map *map, char *key) {
  int i = mapFind(map, key);
  if (i==-1) return NULL;
  return map->table[i].value;
}

void mapDump(Map *map) {
  printf("======= mapDump() ==============\n");
  for (int i=0; i<map->top; i++) {
    Pair *p = &map->table[i];
    printf("  %s %s\n", p->key, (char*) p->value);
  }
}
