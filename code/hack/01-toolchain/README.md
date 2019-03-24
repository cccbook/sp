# hack CPU 工具鏈

## 巨集展開 + 組譯 + 虛擬機執行


```
user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/hack/01-toolchain
$ make
gcc -std=c99 -O0 macro.c map.c util.c -o macro

user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/hack/01-toolchain
$ ./run.sh test/macro/sum
sum=55

```

## 加入 debug 參數 -d

```
user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/hack/01-toolchain
$ ./run.sh test/macro/float -d
====== macroExpand ============
@main  0;JMP    (C4) 4.0  (PI) 3.14159    (main)  // .fset PI
@PI
D=A
@17
swi
// .fput
@18
swi
// .fadd PI
@PI
D=A
@19
swi
// .fput
@18
swi
// .fmul C4
@C4
D=A
@21
swi
// .fput
@18
swi
======= SYMBOL TABLE ===========
map->top = 23 size=1000
72: R2, 2
96: R6, 6
104: SP, 0
184: THAT, 4
320: R10, 10
328: R3, 3
344: R12, 12
352: R7, 7
368: R14, 14
424: THIS, 3
480: SCREEN, 16384
520: LCL, 1
560: R0, 0
584: R4, 4
608: R8, 8
752: KBD, 24576
816: R1, 1
832: R11, 11
840: R5, 5
856: R13, 13
864: R9, 9
872: ARG, 2
880: R15, 15
============= PASS1 ================
00:@main
01:0;JMP
02:
02:(C4) 4.0
label=C4 address=02

  key=C4 *value=2 top=24
04:(PI) 3.14159
label=PI address=04

  key=PI *value=4 top=25
06:
06:(main)
label=main address=06

  key=main *value=6 top=26
06:// .fset PI
06:@PI
07:D=A
08:@17
09:swi
10:// .fput
10:@18
11:swi
12:// .fadd PI
12:@PI
13:D=A
14:@19
15:swi
16:// .fput
16:@18
17:swi
18:// .fmul C4
18:@C4
19:D=A
20:@21
21:swi
22:// .fput
22:@18
23:swi
======= SYMBOL TABLE ===========
map->top = 26 size=1000
72: R2, 2
96: R6, 6
104: SP, 0
184: THAT, 4
256: PI, 4
304: C4, 2
320: R10, 10
328: R3, 3
329: main, 6
344: R12, 12
352: R7, 7
368: R14, 14
424: THIS, 3
480: SCREEN, 16384
520: LCL, 1
560: R0, 0
584: R4, 4
608: R8, 8
752: KBD, 24576
816: R1, 1
832: R11, 11
840: R5, 5
856: R13, 13
864: R9, 9
872: ARG, 2
880: R15, 15
============= PASS2 ================
0000 @main               0006
0001 0;JMP               EA87
0002
0002 (C4) 4.0            00004080
0004 (PI) 3.14159        0FD04049
0006
0006 (main)
0006 // .fset PI
0006 @PI                 0004
0007 D=A                 EC10
0008 @17                 0011
0009 swi                 EBC0
000A // .fput
000A @18                 0012
000B swi                 EBC0
000C // .fadd PI
000C @PI                 0004
000D D=A                 EC10
000E @19                 0013
000F swi                 EBC0
0010 // .fput
0010 @18                 0012
0011 swi                 EBC0
0012 // .fmul C4
0012 @C4                 0002
0013 D=A                 EC10
0014 @21                 0015
0015 swi                 EBC0
0016 // .fput
0016 @18                 0012
0017 swi                 EBC0
======= SYMBOL TABLE ===========
map->top = 26 size=1000
72: R2, 2
96: R6, 6
104: SP, 0
184: THAT, 4
256: PI, 4
304: C4, 2
320: R10, 10
328: R3, 3
329: main, 6
344: R12, 12
352: R7, 7
368: R14, 14
424: THIS, 3
480: SCREEN, 16384
520: LCL, 1
560: R0, 0
584: R4, 4
608: R8, 8
752: KBD, 24576
816: R1, 1
832: R11, 11
840: R5, 5
856: R13, 13
864: R9, 9
872: ARG, 2
880: R15, 15
0006EA87000040800FD040490004EC100011EBC00012EBC00004EC100013EBC00012EBC00002EC100015EBC00012EBC0
PC=0000 I=0006 A=0006 D=0000=00000 m[A]=0004
PC=0001 I=EA87 A=0006 D=0000=00000 m[A]=0004 a=0 c=2A d=0 j=7
PC=0006 I=0004 A=0004 D=0000=00000 m[A]=0FD0
PC=0007 I=EC10 A=0004 D=0004=00004 m[A]=0FD0 a=0 c=30 d=2 j=0
PC=0008 I=0011 A=0011 D=0004=00004 m[A]=0000
PC=0009 I=EBC0 A=0011 D=0004=00004 m[A]=0000 a=0 c=2F d=0 j=0
PC=000A I=0012 A=0012 D=0004=00004 m[A]=0000
PC=000B I=EBC03.141590  A=0012 D=0004=00004 m[A]=0000 a=0 c=2F d=0 j=0
PC=000C I=0004 A=0004 D=0004=00004 m[A]=0FD0
PC=000D I=EC10 A=0004 D=0004=00004 m[A]=0FD0 a=0 c=30 d=2 j=0
PC=000E I=0013 A=0013 D=0004=00004 m[A]=0000
PC=000F I=EBC0 A=0013 D=0004=00004 m[A]=0000 a=0 c=2F d=0 j=0
PC=0010 I=0012 A=0012 D=0004=00004 m[A]=0000
PC=0011 I=EBC06.283180  A=0012 D=0004=00004 m[A]=0000 a=0 c=2F d=0 j=0
PC=0012 I=0002 A=0002 D=0004=00004 m[A]=0000
PC=0013 I=EC10 A=0002 D=0002=00002 m[A]=0000 a=0 c=30 d=2 j=0
PC=0014 I=0015 A=0015 D=0002=00002 m[A]=0000
PC=0015 I=EBC0 A=0015 D=0002=00002 m[A]=0000 a=0 c=2F d=0 j=0
PC=0016 I=0012 A=0012 D=0002=00002 m[A]=0000
PC=0017 I=EBC025.132721  A=0012 D=0002=00002 m[A]=0000 a=0 c=2F d=0 j=0
```
