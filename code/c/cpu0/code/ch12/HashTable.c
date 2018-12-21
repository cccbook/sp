#include "HashTable.h"

void HashTableTest() {
  printf("\n=======HashTableTest()==========\n");
  char *names[] = { "John", "Mary", "George", "Mickey", "Snoopy", "Bob", "Jack" };
  char *ids[]    = { "1",    "2",    "3",      "4",      "5",      "6",   "7" };
  HashTable* table = HashTableNew(3);
  int i;
  for (i=0; i<5; i++)
    HashTablePut(table, names[i], ids[i]);
//  for (i=0; i<7; i++)
//    printf("id=%s\n", HashTableGet(table, names[i]));
//  HashTableEach(table, strPrintln);
  HashTableFree(table);
}

int hash(char *key, int range) {
  int i, hashCode=0;
  for (i=0; i<strlen(key); i++) {
    BYTE value = (BYTE) key[i];
    hashCode += value;
    hashCode %= range;
  }
  return hashCode;
}

Entry* EntryNew(char *key, void *data) {
  Entry* e = ObjNew(Entry, 1);
  e->key = key;
  e->data = data;
  return e;
}

void EntryFree(Entry *e) {
  ObjFree(e);
}

int EntryCompare(Entry *e1, Entry *e2) {
  return strcmp(e1->key, e2->key);
}

HashTable* HashTableNew(int size) {
  Array *table = ArrayNew(size);
  int i;
  for (i=0; i<table->size; i++)
    ArrayAdd(table, ArrayNew(1));
  return table;
}

void HashTableFree(HashTable *table) {
  int ti, hi;
  for (ti=0; ti<table->size; ti++) {
    Array *hitArray = table->item[ti];
    ArrayFree(hitArray, (FuncPtr1) EntryFree);
  }
  ArrayFree(table, NULL);
}

Entry keyEntry;
// 尋找雜湊表中 key 所對應的元素並傳回
void *HashTableGet(HashTable *table, char *key) { 
  int slot = hash(key, table->size);            // 取得雜湊值 (列號) 
  Array *hitArray = (Array*) table->item[slot]; // 取得該列
  // 找出該列中是否有包含 key 的配對
  keyEntry.key = key;
  int keyIdx = ArrayFind(hitArray, &keyEntry, EntryCompare);
  if (keyIdx >= 0) { // 若有，則傳回該配對的資料元素 
    Entry *e = hitArray->item[keyIdx];
    return e->data;
  }
  return NULL; // 否則傳回 NULL 
}

// 將 (key, data) 配對放入雜湊表中 
void HashTablePut(HashTable *table, char *key, void *data) {
  Entry *e;
  int slot = hash(key, table->size);            // 取得雜湊值 (列號) 
  Array *hitArray = (Array*) table->item[slot]; // 取得該列
  keyEntry.key = key;
  int keyIdx = ArrayFind(hitArray, &keyEntry, EntryCompare);
  if (keyIdx >= 0) { // 若有，則傳回該配對的資料元素 
    e = hitArray->item[keyIdx];
    e->data = data;
  } else {
    e= EntryNew(key, data);// 建立配對 
    ArrayAdd(hitArray, e); // 放入對應的列中 
  }
}

void HashTableEach(HashTable *table, FuncPtr1 f) {
  int i, j;
  for (i=0; i<table->count; i++) {
    Array *hits = table->item[i];
    for (j=0; j<hits->count; j++) {
      Entry *e = hits->item[j];
      f(e->data);
    }
  }
}

Array* HashTableToArray(HashTable *table) {
  Array *array = ArrayNew(table->count);
  int i, j;
  for (i=0; i<table->count; i++) {
    Array *hits = table->item[i];
    for (j=0; j<hits->count; j++) {
      Entry *e = hits->item[j];
      ArrayAdd(array, e->data);
    }
  }
  return array;
}
