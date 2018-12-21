# Compiler

## compiler

```
$ gcc main.c lexer.c compiler.c -o compiler
$ ./compiler test/while.c
while (i<10) i = i + 1;

========== lex ==============
token=while
token=(
token=i
token=<
token=10
token=)
token=i
token==
token=i
token=+
token=1
token=;
========== dump ==============
0:while
1:(
2:i
3:<
4:10
5:)
6:i
7:=
8:i
9:+
10:1
11:;
============ parse =============
L0:
t0=i
t1=10
t2 = t0 < t1
goto L1 if T2
t3=i
t4=1
t5 = t3 + t4
i=t5
goto L0
L1:
```

## compileExp.c

```
$ gcc compileExp.c -o compileExp.o -std=c99
$ ./compileExp.o 3+5*8-9/6
=== EBNF Grammar =====
E=T ([+-] T)*
T=F ([*/] F)*
F=N | '(' E ')'
==== parse:3+5*8-9/6 ========
t0=3
t1=5
t2=8
t3=t1*t2
t4=t0+t3
t5=9
t6=6
t7=t5/t6
t8=t4-t7
```
