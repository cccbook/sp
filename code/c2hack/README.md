# Hack Tool Chain

```
user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c2hack/src
$ make
gcc -std=c99 -O0 c0c.c lexer.c compiler.c ir.c irvm.c ir2m0.c map.c util.c -o ../bin/c0c
gcc -std=c99 -O0 asm.c map.c util.c strTable.c -o ../bin/asm
gcc -std=c99 -O0 vm.c util.c -o ../bin/vm
gcc -std=c99 -O0 macro.c map.c util.c -o ../bin/macro

user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c2hack/src
$ make m0run file=../test/m0/sum1
../bin/macro ../test/m0/sum1
../bin/asm ../test/m0/sum1
../bin/vm  ../test/m0/sum1.o0
55

user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c2hack/src
$ make clean
rm -f ../bin/*.o ../bin/*.exe

user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c2hack/src
$ make
gcc -std=c99 -O0 c0c.c lexer.c compiler.c ir.c irvm.c map.c util.c hack.c -o ../bin/c0c
gcc -std=c99 -O0 asm.c map.c util.c strTable.c -o ../bin/asm
gcc -std=c99 -O0 vm.c util.c -o ../bin/vm
gcc -std=c99 -O0 macro.c map.c util.c -o ../bin/macro

user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c2hack/src
$ make as0run file=../test/as0/macro/sumMacro
../bin/macro ../test/as0/macro/sumMacro
../bin/asm ../test/as0/macro/sumMacro
../bin/vm  ../test/as0/macro/sumMacro.bin
sum=55

user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c2hack/src
$ make
gcc -std=c99 -O0 c0c.c lexer.c compiler.c ir.c irvm.c map.c util.c hack.c -o ../bin/c0c
gcc -std=c99 -O0 asm.c map.c util.c strTable.c -o ../bin/asm
gcc -std=c99 -O0 vm.c util.c -o ../bin/vm
gcc -std=c99 -O0 macro.c map.c util.c -o ../bin/macro

user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c2hack/src
$ make c0run file=../test/c0/sum.c0
../bin/c0c ../test/c0/sum.c0 -run

user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c2hack/src
$ make c0run file=../test/c0/sum
../bin/c0c ../test/c0/sum -run
// t1 = 0
@0
D=M
@t1
M=D
// s = t1
@t1
D=M
@s
M=D
// t1 = 1
@1
D=M
@t1
M=D
// i = t1
@t1
D=M
@i
M=D
// (L1)
(L1)
// t2 = i
@i
D=M
@t2
M=D
// t3 = 10
@10
D=M
@t3
M=D
// t4 = t2 <= t3
@t2
D=M
@t3
D=D<=M
@t4
M=D
// ifnot t4 goto L2
@t4
D=M
@L2
D;JNE
// t1 = s
@s
D=M
@t1
M=D
// t2 = i
@i
D=M
@t2
M=D
// t3 = t1 + t2
@t1
D=M
@t2
D=D+M
@t3
M=D
// s = t3
@t3
D=M
@s
M=D
// t1 = i
@i
D=M
@t1
M=D
// t2 = 1
@1
D=M
@t2
M=D
// t3 = t1 + t2
@t1
D=M
@t2
D=D+M
@t3
M=D
// i = t3
@t3
D=M
@i
M=D
// goto L1
@L1
0;JMP
// (L2)
(L2)
===================irRun()=======================
00: t1 = 0 = 0
01: s = t1 = 0
02: t1 = 1 = 1
03: i = t1 = 1
04: (L1) = 4
05: t2 = i = 1
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 0
10: t2 = i = 1
11: t3 = t1 + t2 = 1
12: s = t3 = 1
13: t1 = i = 1
14: t2 = 1 = 1
15: t3 = t1 + t2 = 2
16: i = t3 = 2
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 2
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 1
10: t2 = i = 2
11: t3 = t1 + t2 = 3
12: s = t3 = 3
13: t1 = i = 2
14: t2 = 1 = 1
15: t3 = t1 + t2 = 3
16: i = t3 = 3
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 3
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 3
10: t2 = i = 3
11: t3 = t1 + t2 = 6
12: s = t3 = 6
13: t1 = i = 3
14: t2 = 1 = 1
15: t3 = t1 + t2 = 4
16: i = t3 = 4
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 4
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 6
10: t2 = i = 4
11: t3 = t1 + t2 = 10
12: s = t3 = 10
13: t1 = i = 4
14: t2 = 1 = 1
15: t3 = t1 + t2 = 5
16: i = t3 = 5
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 5
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 10
10: t2 = i = 5
11: t3 = t1 + t2 = 15
12: s = t3 = 15
13: t1 = i = 5
14: t2 = 1 = 1
15: t3 = t1 + t2 = 6
16: i = t3 = 6
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 6
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 15
10: t2 = i = 6
11: t3 = t1 + t2 = 21
12: s = t3 = 21
13: t1 = i = 6
14: t2 = 1 = 1
15: t3 = t1 + t2 = 7
16: i = t3 = 7
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 7
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 21
10: t2 = i = 7
11: t3 = t1 + t2 = 28
12: s = t3 = 28
13: t1 = i = 7
14: t2 = 1 = 1
15: t3 = t1 + t2 = 8
16: i = t3 = 8
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 8
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 28
10: t2 = i = 8
11: t3 = t1 + t2 = 36
12: s = t3 = 36
13: t1 = i = 8
14: t2 = 1 = 1
15: t3 = t1 + t2 = 9
16: i = t3 = 9
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 9
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 36
10: t2 = i = 9
11: t3 = t1 + t2 = 45
12: s = t3 = 45
13: t1 = i = 9
14: t2 = 1 = 1
15: t3 = t1 + t2 = 10
16: i = t3 = 10
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 10
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 45
10: t2 = i = 10
11: t3 = t1 + t2 = 55
12: s = t3 = 55
13: t1 = i = 10
14: t2 = 1 = 1
15: t3 = t1 + t2 = 11
16: i = t3 = 11
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 11
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 0
08: ifnot t4(=0) goto L2 = 18
18: (L2) = 18
```