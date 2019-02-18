#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// #include <sys/mmap.h>

unsigned char addCode[] = {
  0x55,                      // push   %rbp
  0x48,0x89,0xe5,            // mov    %rsp,%rbp
  0x89,0x4d,0x10,            // mov    %ecx,0x10(%rbp)
  0x89,0x55,0x18,            // mov    %edx,0x18(%rbp)
  0x8b,0x55,0x10,            // mov    0x10(%rbp),%edx
  0x8b,0x45,0x18,            // mov    0x18(%rbp),%eax
  0x01,0xd0,                 // add    %edx,%eax
  0x5d,                      // pop    %rbp
  0xc3,                      // retq
  0x90,                      // nop
  0x90,                      // nop
  0x90,                      // nop
  0x90,                      // nop
  0x90,                      // nop
  0x90,                      // nop
  0x90,                      // nop
  0x90,                      // nop
  0x90,                      // nop
  0x90,                      // nop
  0x90,                      // nop
  0x90                       // nop
};

int f(int a, int b) {
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;
  a = a+b;

}

int main() {
  int (*add)(int a, int b);
  int codeSize = sizeof(addCode);
  printf("codeSize=%d\n", codeSize);
  unsigned char *mCode = malloc(codeSize + 100);
  mCode = mCode + (8 - ((unsigned int) mCode) % 8);
  if (mprotect(mCode, codeSize, PROT_READ | PROT_WRITE | PROT_EXEC))
    perror("mprotect");
  printf("mCode=%p\n", mCode);
  memcpy(f, addCode, codeSize);
  mCode = (unsigned char *)f;
  printf("mCode[0]=%d\n", mCode[0]);
  // add = (int (*)(int, int)) addCode;
  // add = (int (*)(int, int)) mCode;
  add = (int (*)(int, int)) f;
  printf("add(5, 8)=%d\n", add(3, 8));
}
