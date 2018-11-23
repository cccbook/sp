#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "c6.h"

// ================ Map ====================
Map* c6mapNew(Map *map, Pair *list, int size) {
  map->list = list;
  map->size = size;
  map->top = size;
  return map;
}

Pair c6mapAdd(Map *map, char *key, void *value) {
  assert(map->top < map->size);
  Pair p = { key, value };
  map->list[map->top++] = p;
  return p;
}

int c6mapFind(Map *map, char *key) {
  for (int i=0; i<map->top; i++) {
    if (strcmp(map->list[i].key, key)==0)
      return i;
  }
  return -1;
}

void* c6mapLookup(Map *map, char *key) {
  int i = c6mapFind(map, key);
  if (i==-1) return NULL;
  return map->list[i].value;
}

// ================= Binary ==================
static string h2b[] = {
  "0000", "0001", "0010", "0011",
  "0100", "0101", "0110", "0111", 
  "1000", "1001", "1010", "1011",
  "1100", "1101", "1110", "1111"};

static char hexDigits[] = "0123456789ABCDEF";

void c6htob(string hex, string binary) {
  for (int i=0; hex[i] != '\0'; i++) {
    char *ptr = strchr(hexDigits, hex[i]);
    assert(ptr != NULL);
    char h = ptr - hexDigits;
    sprintf(&binary[4*i], "%s", h2b[h]);
  }
}

void c6itob(int i, string binary) {
  char hex[100];
  sprintf(hex, "%04X", i);
  c6htob(hex, binary);
}

int c6btoi(string binary) {
  int result = 0;
  int len = strlen(binary);
  for(int i=0; i < len; i++) {
    result <<= 1;
    if (binary[i] == '1') result += 1;
  }
  return result;
}

// ================== String Table ======================
void c6strTable(StrTable *t, char *text, int size) {
  t->text = text;
  t->size = size;
  t->textEnd = text;
}

char *c6strNew(StrTable *t, char *str) {
  char *strBegin = t->textEnd;
  strcpy(t->textEnd, str);
  t->textEnd += strlen(str) + 1;
  return strBegin;
}

