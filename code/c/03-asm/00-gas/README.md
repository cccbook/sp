# x86 64 位元版組合語言




## windows


* [hello world, C and GNU as](https://www.chocolatesparalucia.com/2010/09/hello-world-c-and-gnu-as/)

```
as -o hello.o hello.s

ld -o hello.exe
/mingw/lib/crt2.o
C:/MinGW/bin/../lib/gcc/mingw32/3.4.5/crtbegin.o
-LC:/MinGW/bin/../lib/gcc/mingw32/3.4.5
-LC:/MinGW/lib hello.o
-lmingw32 -lgcc -lmsvcrt -lkernel32
C:/MinGW/bin/../lib/gcc/mingw32/3.4.5/crtend.o
```

But it’s better to just type gcc -o hello.exe hello.s 

* https://en.wikibooks.org/wiki/X86_Assembly/GAS_Syntax#Communicating_directly_with_the_operating_system
* https://en.wikipedia.org/wiki/X86-64


## Linux

學習 -- http://cs.lmu.edu/~ray/notes/gasexamples/

參考 -- https://eli.thegreenplace.net/2011/09/06/stack-frame-layout-on-x86-64/

這些範例必須在 Linux 下執行， windows 與 mac 不行！

目前只有 hello.s 在 linux 下可以執行，其他的範例都會出現類似下列的錯誤！

```
root@localhost:~/ccc/sp/code/c/03-asm/00-gas# gcc hola.s && ./a.out             /usr/bin/ld: /tmp/ccr7JgHC.o: relocation R_X86_64_32S against `.text' can not be used when making a PIE object; recompile with -fPIC
/usr/bin/ld: final link failed: Nonrepresentable section on output
collect2: error: ld returned 1 exit status
```

