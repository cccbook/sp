# c2hack 編譯組譯工具鏈

$ make
gcc -std=c99 -O0 asm.c map.c strTable.c util.c -o asm
gcc -std=c99 -O0 vm.c util.c -o vm
gcc -std=c99 -O0 macro.c map.c util.c -o macro

$ ./as.sh ../test/ext/floatMacro
iFile=../test/ext/floatMacro.m oFile=../test/ext/floatMacro.asm
@main
0;JMP

(C4) 4.0
(PI) 3.14159

(main)
// .fset PI
@PI
D=A
@16
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
31: ARG, 2
101: THIS, 3
135: R0, 0
136: R1, 1
137: R2, 2
138: R3, 3
139: R4, 4
140: R5, 5
141: R6, 6
142: R7, 7
143: R8, 8
144: R9, 9
149: SCREEN, 16384
184: SP, 0
360: R10, 10
361: R11, 11
362: R12, 12
363: R13, 13
364: R14, 14
365: R15, 15
646: KBD, 24576
960: LCL, 1
966: THAT, 4
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
08:@16
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
31: ARG, 2
101: THIS, 3
126: PI, 4
135: R0, 0
136: R1, 1
137: R2, 2
138: R3, 3
139: R4, 4
140: R5, 5
141: R6, 6
142: R7, 7
143: R8, 8
144: R9, 9
149: SCREEN, 16384
184: SP, 0
360: R10, 10
361: R11, 11
362: R12, 12
363: R13, 13
364: R14, 14
365: R15, 15
646: KBD, 24576
722: main, 6
884: C4, 2
960: LCL, 1
966: THAT, 4
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
0008 @16                 0010
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
3.141590 6.283180 25.132721
