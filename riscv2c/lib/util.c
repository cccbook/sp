#include "util.h"

int readText(char *fileName, char *text, int size) {
  FILE *file = fopen(fileName, "r");
  int len = fread(text, 1, size, file);
  text[len] = '\0';
  fclose(file);
  return len;
}

int isMember(char *token, char *set) {
  char eSet[SMAX], eToken[SMAX];
  sprintf(eSet, " %s ", set);
  sprintf(eToken, " %s ", token);
  return (*token != '\0' && strstr(eSet, eToken) != NULL);
}
