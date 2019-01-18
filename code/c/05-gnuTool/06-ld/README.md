# ld 連結器

* 參考 https://www.slideshare.net/jserv/helloworld-internals 32 頁開始！

但是在 Windows 中連結會失敗，可能要改用 Linux ...

* 失敗原因參考 -- https://stackoverflow.com/questions/32164478/when-using-ld-to-link-undefined-reference-to-main

```
PS D:\ccc\book\sp\code\c\05-gnuTool\06-ld> gcc -c a.c b.c
PS D:\ccc\book\sp\code\c\05-gnuTool\06-ld> ld a.o b.o -e main -o ab
C:\Program Files (x86)\CodeBlocks\MinGW\bin\ld.exe: warning: cannot find entry symbol main; defaulting to 00401000


PS D:\ccc\book\sp\code\c\05-gnuTool\06-ld> objdump -h a.o

a.o:     file format pe-i386

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         00000034  00000000  00000000  000000b4  2**2
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000000  00000000  00000000  00000000  2**2
                  ALLOC, LOAD, DATA
  2 .bss          00000000  00000000  00000000  00000000  2**2
                  ALLOC
  3 .rdata$zzz    00000014  00000000  00000000  000000e8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
PS D:\ccc\book\sp\code\c\05-gnuTool\06-ld> objdump -h b.o

b.o:     file format pe-i386

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         00000024  00000000  00000000  000000b4  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .data         00000004  00000000  00000000  000000d8  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  00000000  00000000  00000000  2**2
                  ALLOC
  3 .rdata$zzz    00000014  00000000  00000000  000000dc  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
```