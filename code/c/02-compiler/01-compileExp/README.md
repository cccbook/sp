# compileExp

```
user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/02-compiler/01-compileExp
$ gcc compileExp.c -o compileExp

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/02-compiler/01-compileExp
$ ./compileExp 1+3*x
=== EBNF Grammar =====
E=T ([+-] T)*
T=F ([*/] F)*
F=Number | Id | '(' E ')'
==== parse:1+3*x ========
t0=1
t1=3
t2=x
t3=t1*t2
t4=t0+t3
```
