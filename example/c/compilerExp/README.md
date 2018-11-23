# Compiler

# compileExp.c

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
