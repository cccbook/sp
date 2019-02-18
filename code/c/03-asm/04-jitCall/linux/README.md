# JIT 立即編譯的範例

```
root@localhost:~/ccc/sp/code/c/03-asm/01-add# gcc -c add.c -o add.o
root@localhost:~/ccc/sp/code/c/03-asm/01-add# objdump -d add.o

add.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <add>:
   0:   55                      push   %rbp
   1:   48 89 e5                mov    %rsp,%rbp
   4:   89 7d fc                mov    %edi,-0x4(%rbp)
   7:   89 75 f8                mov    %esi,-0x8(%rbp)
   a:   8b 55 fc                mov    -0x4(%rbp),%edx
   d:   8b 45 f8                mov    -0x8(%rbp),%eax
  10:   01 d0                   add    %edx,%eax
  12:   5d                      pop    %rbp
  13:   c3                      retq

```

結果在 linux 跑會失敗， core dump

```
root@localhost:~/ccc/sp/code/c/03-asm/04-jitCall/linux# gcc jitCall.c -o jitCallroot@localhost:~/ccc/sp/code/c/03-asm/04-jitCall/linux# ./jitCall
Segmentation fault (core dumped)
root@localhost:~/ccc/sp/code/c/03-asm/04-jitCall/linux# ls
jitCall  jitCall.c  jitCall.exe.stackdump  jitCall.o  jitRef.md  README.md
```

## 參考文獻

* [Jserv's blog: AsmJit : C++ 封裝的 Just-In-Time Assembler](http://blog.linux.org.tw/~jserv/archives/002089.html)
* https://github.com/asmjit/asmjit
* C -- https://github.com/spencertipping/jit-tutorial
* C++ -- https://github.com/sol-prog/x86-64-minimal-JIT-compiler-Cpp (讚!)
