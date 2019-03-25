#include "../util.h"

void main() {
  char buf[SMAX];
  format(buf, "@${1};D=M;${2};M=D", "x", "t1");
  printf("buf=|%s|\n", buf);
  format(buf, "abcd", "x", "t1");
  printf("buf=|%s|\n", buf);
}