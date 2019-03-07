#include "Lib.h"

char SPLITER[] = " \t\n\r~!@#$%^&*()_+{}:\"<>?-=[]|\\;',./";
char SPACE[] = " \t\n\r";
char ALPHA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char DIGIT[] = "0123456789";
char NAME_CHAR[] = "_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

// 記憶體配置函數 
int newMemoryCount = 0;
void* newMemory(int size) {
  void *ptr=malloc(size);
  assert(ptr != NULL);
  memset(ptr, 0, size);
//  printf("memGet:%p\n", ptr);
  newMemoryCount++;
  return ptr;
}

int freeMemoryCount=0;
void freeMemory(void *ptr) {
//  printf("memFree:%p\n", ptr);
  free(ptr);
  freeMemoryCount++;
}

void checkMemory() {
  printf("newMemoryCount=%d freeMemoryCount=%d\n", newMemoryCount, freeMemoryCount);
}

// 檔案輸出入 
BYTE* newFileBytes(char *fileName, int *sizePtr) {
  FILE *file = fopen(fileName, "rb");
  fseek(file, 0 , SEEK_END);
  long size = ftell(file);
  rewind(file);
  BYTE *buffer = (char*) newMemory(size+1);
  fread (buffer,size,1,file);
  fclose(file);
  *sizePtr = size;
  return buffer;
}

char* newFileStr(char *fileName) {
  int size;
  BYTE *buffer = newFileBytes(fileName, &size);
  buffer[size] = '\0';
  return (char*) buffer;
}

char *newStr(char *str) {
  char *rzStr = newMemory(strlen(str)+1);
  strcpy(rzStr, str);
  return rzStr;
}

char *newSubstr(char *str, int i, int len) {
  char *rzStr = newMemory(len+1);
  strSubstr(rzStr, str, i, len);
  return rzStr;
}

// 字串函數 
void strPrint(void *data) {
  printf("%s ", data);
}

void strPrintln(void *data) {
  printf("%s\n", data);
}

BOOL strHead(char *str, char *head) { 
  return (strncmp(str, head, strlen(head))==0);
}

BOOL strTail(char *str, char *tail) {
  int strLen = strlen(str), tailLen = strlen(tail);
  if (strLen < tailLen) return FALSE;
  return (strcmp(str+strLen-tailLen, tail)==0);
}

int strCountChar(char *str, char *charSet) {
  int i, count=0;
  for (i=0; i<strlen(str); i++)
    if (strMember(str[i], charSet))
      count++;
  return count;
}

void strSubstr(char *substr, char *str, int i, int len) {
  strncpy(substr, &str[i], len);
  substr[len]='\0';
}
 
BOOL strPartOf(char *token, char *set) {
  ASSERT(token != NULL && set != NULL);
  ASSERT(strlen(token) < 100);
  char ttoken[100];
  sprintf(ttoken, "|%s|", token);
  return (strstr(set, ttoken)!=NULL);
}

void strTrim(char *trimStr, char *str, char *set) {
  char *start, *stop;
  for (start = str; strMember(*start, set); start++);
  for (stop = str+strlen(str)-1; stop > str && strMember(*stop, set); stop--);
  if (start <= stop) {
    strncpy(trimStr, start, stop-start+1);
    trimStr[stop-start+1]='\0';
  } else
    strcpy(trimStr, "");
}

void strReplace(char *str, char *from, char to) {
  int i;
  for (i=0; i<strlen(str); i++)
    if (strMember(str[i], from))
      str[i] = to;
}

char tspaces[MAX_LEN];
char* strSpaces(int level) {
  assert(level < MAX_LEN);
  memset(tspaces, ' ', MAX_LEN);
  tspaces[level] = '\0';
  return tspaces;
}

void strToUpper(char *str) {
  int i;
  for (i = 0; i<strlen(str); i++)
    str[i] = toupper(str[i]);
}
