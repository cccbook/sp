#include <stdio.h>

unsigned char addCode[] = {
   0x55,                     // push   %rbp
   0x48,0x89,0xe5,           // mov    %rsp,%rbp
   0x89,0x7d,0xfc,           // mov    %edi,-0x4(%rbp)
   0x89,0x75,0xf8,           // mov    %esi,-0x8(%rbp)
   0x8b,0x55,0xfc,           // mov    -0x4(%rbp),%edx
   0x8b,0x45,0xf8,           // mov    -0x8(%rbp),%eax
   0x01,0xd0,                // add    %edx,%eax
   0x5d,                     // pop    %rbp
   0xc3                      // retq
};

int (*add)(int a, int b);

int main() {
  add = (int (*)(int, int)) addCode;
  printf("add(5, 8)=%d\n", add(5, 8));
}
