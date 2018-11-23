# 系統程式簡介

* [nand2tetris -- Assembler](http://www.nand2tetris.org/lectures/PDF/lecture%2006%20assembler.pdf)

## 語法理論

* [人工智慧 -- 語言處理](https://mdbookspace.com/view/ai/linguistics.md)
* [計算語言學](https://mdbookspace.com/view/ccc/NLP.md)

```
// === EBNF Grammar =====
// E=T ([+-] T)*
// T=F ([*/] F)?
// T=[0-9] | (E)
```

## 語言生成

### 運算式生成

```
$ gcc genExp.c rlib.c -o genExp.o
$ ./genExp.o
9*2(9/2)/(2/(0/(5)-3))-3/8+1*8+0*9
3
(8/5)*9
9/5
8
2*7
1+8
4-5-(0)
(0*5+1*1-(6*(6*9))-3/8)*4
3
```

