#include "map.h"

// 這個 hash 函數比較簡單，但是 R1, R2, R3 這樣的字串會連續，所以不是很好。
// 如果要避免碰撞後搜尋次數太多，可以用更好的 hash 函數
unsigned int hash(char *key) {
  char *p = key;
  unsigned int  h = 37;
  while (*p != '\0') {
    h = (h << 4) + h + *p; // h = h*17 + *p; 為了加速不用乘法 ....
    p++;
  }
  return h << 6 + (p-key);
}

Map* mapNew(Map *map, int size) {
  map->table = calloc(size, sizeof(Pair));
  map->size = size;
  map->top = 0;
  return map;
}

int mapFindIdx(Map *map, char *key) {
  int h = hash(key) % map->size;
  while (map->table[h].key != NULL) {
    if (strcmp(map->table[h].key, key)==0) break;
    h = (h+1) % map->size;
  }
  return h;
}

Pair *mapFind(Map *map, char *key) {
  int h = mapFindIdx(map, key);
  return &map->table[h];
}

Pair* mapAdd(Map *map, char *key, void *value) {
  assert(map->top < map->size);
  Pair *p = mapFind(map, key);
  if (p->key == NULL) map->top++;
  p->key = key;
  p->value = value;
  return p;
}

void* mapLookup(Map *map, char *key) {
  Pair *p = mapFind(map, key);
  return p->value;
}

void mapAddAll(Map *map, Pair *list, int top) {
  for (int i=0; i<top; i++) {
    // printf("%d : key=%s value=%s\n", i, list[i].key, list[i].value);
    mapAdd(map, list[i].key, list[i].value);
  }
}

void mapDump(Map *map) {
  printf("======= mapDump() ==============\n");
  for (int i=0; i<map->size; i++) {
    Pair *p = &map->table[i];
    if (p->key != NULL) {
      printf("%03d:  %-20s %s\n", i, p->key, (char*) p->value);
    }
  }
}

void mapDumpInt(Map *map) {
  printf("======= mapDumpInt() ==============\n");
  for (int i=0; i<map->size; i++) {
    Pair *p = &map->table[i];
    if (p->key != NULL) {
      printf("%03d:  %-20s %d\n", i, p->key, *(int*) p->value);
    }
  }
}

void mapFree(Map *map) {
  free(map->table);
}
