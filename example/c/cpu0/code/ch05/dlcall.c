// 編譯指令：gcc -o dl_call dl_call.c –ldl (必須在 Linux 中編譯， Cygwin 與 MinGW 不行)
#include <dlfcn.h>

int main(void) {
 void *handle = dlopen ("libm.so", RTLD_LAZY);
 double (*cosine)(double);
 cosine = dlsym(handle, "cos");
 printf ("%f\n", (*cosine)(2.0));
 dlclose(handle);
 return 0;
}