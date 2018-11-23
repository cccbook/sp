#include <stdio.h>

#define SIZE 3
int main() {
  int a[SIZE];
  for (int i=0; i<SIZE; i++) {
    scanf("%d", &a[i]);    
    printf("%d", a[i]);    
  }
}