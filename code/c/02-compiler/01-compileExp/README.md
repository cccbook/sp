# compileExp

```
$ gcc compileExp.c -o compileExp

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
