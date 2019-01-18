# nm (Nemonic Name)

印出符號表

```
PS D:\ccc\book\sp\code\c\05-gnuTool\05-nm> gcc -c test.c -o test.o
PS D:\ccc\book\sp\code\c\05-gnuTool\05-nm> nm test.o
00000000 b .bss
00000000 d .data
00000000 i .drectve
00000000 r .rdata
00000000 r .rdata$zzz
00000000 t .text
00000000 D _a
00000004 C _b
00000004 C _c
00000000 T _foo
         U _printf
00000004 D _str
```