# compiler

```
PS D:\ccc\book\sp\code\c\02-compiler\04-compiler-ir> make
gcc -std=c99 -O0 lexer.c compiler.c main.c ir.c -o compiler
PS D:\ccc\book\sp\code\c\02-compiler\04-compiler-ir> ./compiler test/sum.c

s=0;
i=1;
while (i < 10) {
  s = s + i;
  i = i + 1;
}


========== lex ==============
token=s
token==
token=0
token=;
token=i
token==
token=1
token=;
token=while
token=(
token=i
token=<
token=10
token=)
token={
token=s
token==
token=s
token=+
token=i
token=;
token=i
token==
token=i
token=+
token=1
token=;
token=}
========== dump ==============
0:s
1:=
2:0
3:;
4:i
5:=
6:1
7:;
8:while
9:(
10:i
11:<
12:10
13:)
14:{
15:s
16:=
17:s
18:+
19:i
20:;
21:i
22:=
23:i
24:+
25:1
26:;
27:}
============ parse =============
T1 = 0
s = T1
T2 = 1
i = T2
(L1)
T3 = i
T4 = 10
t5 = t3 < t4
if T5 goto L1
T6 = s
T7 = i
t8 = t6 + t7
s = T8
T9 = i
T10 = 1
t11 = t9 + t10
i = T11
goto L1
(L2)
```