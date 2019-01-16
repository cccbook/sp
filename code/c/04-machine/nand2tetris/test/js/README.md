# Assembler -- JavaScript

## JavaScript 版組譯器的用法

```
$ node js/ash.js Add
[
  "// This file is part of www.nand2tetris.org",
  "// and the book \"The Elements of Computing Systems\"",
  "// by Nisan and Schocken, MIT Press.",
  "// File name: projects/06/add/Add.asm",
  "",
  "// Computes R0 = 2 + 3",
  "",
  "@2",
  "D=A",
  "@3",
  "D=D+A",
  "@0",
  "M=D",
  ""
]
============== pass1 ================
 p: {"type":"A","arg":"2"}
008:0000 @2
 p: {"type":"C","c":"A","d":"D","j":""}
009:0001 D=A
 p: {"type":"A","arg":"3"}
010:0002 @3
 p: {"type":"C","c":"D+A","d":"D","j":""}
011:0003 D=D+A
 p: {"type":"A","arg":"0"}
012:0004 @0
 p: {"type":"C","c":"D","d":"M","j":""}
013:0005 M=D
============== pass2 ================
008:0000000000000010 @2
009:1110110000010000 D=A
010:0000000000000011 @3
011:1110000010010000 D=D+A
012:0000000000000000 @0
013:1110001100001000 M=D
```