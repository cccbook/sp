#include <stdio.h>

unsigned char code[] = {
   0x55,             // push   %ebp
   0x89, 0xe5,       // mov    %esp,%ebp
   0x8b, 0x55, 0x08, // mov    0x8(%ebp),%edx
   0x8b, 0x45, 0x0c, // mov    0xc(%ebp),%eax
   0x01, 0xd0,       // add    %edx,%eax
   0x5d,             // pop    %ebp
   0xc3,             // ret
   0x90,             // nop
   0x90,             // nop
   0x90              // nop
};

int (*add)();

int main() {
  add = (int (*)()) code;
  int t = add(5, 8);
  printf("add(5, 8)=%d\n", t);
}
