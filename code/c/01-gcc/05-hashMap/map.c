#include "map.h"

unsigned int hash(char *key) {
  char *p = key;
  unsigned int  h = 37;
  while (*p != '\0') {
    h = h * 147 + *p++;
  }
  return h;
}

Map* mapNew(Map *map, int size) {
  map->table = malloc(size*sizeof(Pair));
  memset(map->table, 0, size*sizeof(Pair));
  map->size = size;
  map->top = 0;
  return map;
}

Pair* mapAdd(Map *map, char *key, void *value) {
  assert(map->top < map->size);
  unsigned int h = hash(key) % map->size;
  while (map->table[h].key != NULL) {
    if (strcmp(map->table[h].key, key)==0) break;
    h = (h+1) % map->size;
  }
  map->table[h].key = key;
  map->table[h].value = value;
  return &map->table[h];
}

int mapFind(Map *map, char *key) {
  int h = hash(key) % map->size;
  while (map->table[h].key != NULL) {
    if (strcmp(map->table[h].key, key)==0) return h;
    h = (h+1) % map->size;
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
  for (int i=0; i<map->size; i++) {
    Pair *p = &map->table[i];
    printf("%d:  %s %s\n", i, p->key, (char*) p->value);
  }
}
