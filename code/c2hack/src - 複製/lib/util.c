#include "util.h"

// ================= Binary ==================
static char* h2b[] = {
  "0000", "0001", "0010", "0011",
  "0100", "0101", "0110", "0111", 
  "1000", "1001", "1010", "1011",
  "1100", "1101", "1110", "1111"};

static char hexDigits[] = "0123456789ABCDEF";

void htob(char* hex, char* binary) {
  for (int i=0; hex[i] != '\0'; i++) {
    char *ptr = strchr(hexDigits, hex[i]);
    assert(ptr != NULL);
    char h = ptr - hexDigits;
    sprintf(&binary[4*i], "%s", h2b[h]);
  }
}

void itob(int i, char* binary) {
  char hex[100];
  sprintf(hex, "%04X", i);
  htob(hex, binary);
}

int btoi(char* binary) {
  int result = 0;
  int len = strlen(binary);
  for(int i=0; i < len; i++) {
    result <<= 1;
    if (binary[i] == '1') result += 1;
  }
  return result;
}