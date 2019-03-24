# Nand2tetris : Assembler


```
user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/03-nand2tetris/asm
$ make
gcc -std=c99 -O0 asm.c c6.c -o asm

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/03-nand2tetris/asm
$ ./asm ../test/Add
======= SYMBOL TABLE ===========
0: R0, 0
1: R1, 1
2: R2, 2
3: R3, 3
4: R4, 4
5: R5, 5
6: R6, 6
7: R7, 7
8: R8, 8
9: R9, 9
10: R10, 10
11: R11, 11
12: R12, 12
13: R13, 13
14: R14, 14
15: R15, 15
16: SCREEN, 16384
17: KBD, 24576
18: SP, 0
19: LCL, 1
20: ARG, 2
21: THIS, 3
22: THAT, 4
============= PASS1 ================
00:@2
01:D=A
02:@3
03:D=D+A
04:@0
05:M=D
======= SYMBOL TABLE ===========
0: R0, 0
1: R1, 1
2: R2, 2
3: R3, 3
4: R4, 4
5: R5, 5
6: R6, 6
7: R7, 7
8: R8, 8
9: R9, 9
10: R10, 10
11: R11, 11
12: R12, 12
13: R13, 13
14: R14, 14
15: R15, 15
16: SCREEN, 16384
17: KBD, 24576
18: SP, 0
19: LCL, 1
20: ARG, 2
21: THIS, 3
22: THAT, 4
============= PASS2 ================
  @2                   0000000000000010 0002
  D=A                  1110110000010000 ec10
  @3                   0000000000000011 0003
  D=D+A                1110000010010000 e090
  @0                   0000000000000000 0000
  M=D                  1110001100001000 e308
```

