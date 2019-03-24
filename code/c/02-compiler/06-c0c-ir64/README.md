# Compiler

```
$ make
gcc -std=c99 -O0 lexer.c compiler.c main.c ir.c irvm.c map.c -o c0c

$ ./c0c test/stmt0.c -r
===================irRun()=======================
t1 = 3
t2 = 5
t3 = t1 + t2 = 8
a = t3 = 8
```