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

在 mac 底下若有括號必須外面先用 '...' 刮起來，如下所示，否則會錯誤。

```
csienqu-teacher:01-compileExp csienqu$ ./compileExp.o '(3+5)*x/y'
=== EBNF Grammar =====
E=T ([+-] T)*
T=F ([*/] F)*
F=Number | Id | '(' E ')'
==== parse:(3+5)*x/y ========
t0=3
t1=5
t2=t0+t1
t3=x
t4=t2*t3
t5=y
t6=t4/t5
```