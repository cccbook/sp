#ifndef TREE_H
#define TREE_H

#include "Array.h"

typedef struct {
  char *type;
  char *value;
  Array* childs;
} Tree;

Tree* TreeNew(char *pType, char *pValue);
void TreeFree(Tree *tree);
void TreeAddChild(Tree *tree, Tree *child);
void TreePrint(Tree *tree);

#endif
