# JIT 立即編譯的範例

```
user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/03-asm/01-add
$ gcc -c add.c -o add.o

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/03-asm/01-add
$ objdump -d add.o

add.o：     檔案格式 pe-x86-64


Disassembly of section .text:

0000000000000000 <add>:
   0:   55                      push   %rbp
   1:   48 89 e5                mov    %rsp,%rbp
   4:   89 4d 10                mov    %ecx,0x10(%rbp)
   7:   89 55 18                mov    %edx,0x18(%rbp)
   a:   8b 55 10                mov    0x10(%rbp),%edx
   d:   8b 45 18                mov    0x18(%rbp),%eax
  10:   01 d0                   add    %edx,%eax
  12:   5d                      pop    %rbp
  13:   c3                      retq
  14:   90                      nop
  15:   90                      nop
  16:   90                      nop
  17:   90                      nop
  18:   90                      nop
  19:   90                      nop
  1a:   90                      nop
  1b:   90                      nop
  1c:   90                      nop
  1d:   90                      nop
  1e:   90                      nop
  1f:   90                      nop


```

失敗

```
user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/03-asm/04-jitCall/win64
$ gcc jitCall.c -o jitCall

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/03-asm/04-jitCall/win64
$ ./jitCall
Segmentation fault (核心已傾印)

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/03-asm/04-jitCall/win64

```

失敗的可能原因


```
on 32 bit Windows there is a memory limit of 2 GB per process. If you are running the "Basic Terrain Analysis" module, 11 output grids (and some temporary grids) will be created - each the size of the input grid. They all have to fit in the RAM. Please consider this when running this module. If this limit is reached or exceeded you get an access violation.

Since the memory limit is not a shortcoming of SAGA and, as you already said, the module is working as expected when using smaller input grids, I would not consider this a bug.

Regards,
Manfred

The limitation is a result from the x86 architecture, where the maximum addressable memory is about 3 GB. So you will see a similar behavior on Linux too. The only way to get past this limit is to upgrade to a 64 bit OS if your hardware is capable.

There is a way to work around your problem:
Do you really need all the results from this module. All of the calculations in this modules are taken from other terrain analysis modules. Please have a look at them. You can run the analysis one by one with more options and reduce the number of grids loaded at the same time.

Manfred
```


## 參考文獻

* [Jserv's blog: AsmJit : C++ 封裝的 Just-In-Time Assembler](http://blog.linux.org.tw/~jserv/archives/002089.html)
* https://github.com/asmjit/asmjit
* C -- https://github.com/spencertipping/jit-tutorial
* C++ -- https://github.com/sol-prog/x86-64-minimal-JIT-compiler-Cpp (讚!)
