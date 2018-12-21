# Compiler

## compileExp.js

```
$ node .\compileExp.js
=== EBNF Grammar =====
E=T ([+-] T)*
T=F ([*/] F)*
F=NUMBER | ID | '(' E ')'
text=32+5*(182+degree*4-20)
tokens=["32","+","5","*","(","182","+","degree","*","4","-","20",")"]
= T0 32
= T2 5
= T3 182
= T5 4
* T6 degree T5
* T4 T3 T6
= T8 20
- T7 T4 T8
- T9 T8 T7
- T7 T7 T9
symTable={"degree":"ID"}
```