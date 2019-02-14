# JIT 立即編譯的範例

```
PS D:\ccc\book\sp\code\c\03-asm\jit> gcc -fverbose-asm -S add.c -o add.s
PS D:\ccc\book\sp\code\c\03-asm\jit> gcc -c add.s -o add.o
PS D:\ccc\book\sp\code\c\03-asm\jit> objdump -d add.o

add.o:     file format pe-i386


Disassembly of section .text:

00000000 <_add>:
   0:   55                      push   %ebp
   1:   89 e5                   mov    %esp,%ebp
   3:   8b 55 08                mov    0x8(%ebp),%edx
   6:   8b 45 0c                mov    0xc(%ebp),%eax
   9:   01 d0                   add    %edx,%eax
   b:   5d                      pop    %ebp
   c:   c3                      ret
   d:   90                      nop
   e:   90                      nop
   f:   90                      nop
PS D:\ccc\book\sp\code\c\03-asm\jit> gcc addMain.c add.c -o addMain
PS D:\ccc\book\sp\code\c\03-asm\jit> ./addMain
add(5, 8)=13
PS D:\ccc\book\sp\code\c\03-asm\jit> gcc addJit.c -o addJit
PS D:\ccc\book\sp\code\c\03-asm\jit> ./addJit
add(5, 8)=13
```

## 參考文獻

* [Jserv's blog: AsmJit : C++ 封裝的 Just-In-Time Assembler](http://blog.linux.org.tw/~jserv/archives/002089.html)
* https://github.com/asmjit/asmjit
* C -- https://github.com/spencertipping/jit-tutorial
* C++ -- https://github.com/sol-prog/x86-64-minimal-JIT-compiler-Cpp (讚!)
