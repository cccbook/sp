#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Array.h"

typedef struct {
  char *key;
  void *data;
} Entry;

Entry* EntryNew(char *key, void *data);
int EntryCompare(Entry *e1, Entry *e2);

int hash(char *key, int range);

#define HashTable Array

HashTable* HashTableNew(int size);
void HashTableFree(HashTable *table);
void HashTablePut(HashTable *table, char *key, void *data);
void *HashTableGet(HashTable *table, char *key);
void HashTableEach(HashTable *table, FuncPtr1 f);
Array* HashTableToArray(HashTable *table);
void HashTableTest();

#endif
