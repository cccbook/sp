#include "sum.h"

int sum(int n) {
  int s=0;
  for (int i=0; i<=n; i++) {
    s=s+i;
  }
  return s;
}
