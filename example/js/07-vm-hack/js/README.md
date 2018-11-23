# Virtual Machine -- VM

## vmh.js

```
$ node vmh BasicTest
[
  "// This file is part of www.nand2tetris.org",
  "// and the book \"The Elements of Computing Systems\"",
  "// by Nisan and Schocken, MIT Press.",
  "// File name: projects/07/MemoryAccess/BasicTest/BasicTest.vm",
  "",
  "// Executes pop & push commands using the virtual memory segments.",
  "push constant 10",
  "pop local 0",
  "push constant 21",
  "push constant 22",
  "pop argument 2",
  "pop argument 1",
  "push constant 36",
  "pop this 6",
  "push constant 42",
  "push constant 45",
  "pop that 5",
  "pop that 2",
  "push constant 510",
  "pop temp 6",
  "push local 0",
  "push that 5",
  "add",
  "push argument 1",
  "sub",
  "push this 6",
  "push this 6",
  "add",
  "sub",
  "push temp 6",
  "add",
  ""
]
============== pass1 ================
// push constant 10
@10
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop local 0
@SP
M=M-1
@LCL
AD=M
@R15
M=D
@SP
A=M
D=M
@R15
A=M
M=D
// push constant 21
@21
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 22
@22
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop argument 2
@SP
M=M-1
@2
D=A
@ARG
A=M
AD=D+A
@R15
M=D
@SP
A=M
D=M
@R15
A=M
M=D
// pop argument 1
@SP
M=M-1
@1
D=A
@ARG
A=M
AD=D+A
@R15
M=D
@SP
A=M
D=M
@R15
A=M
M=D
// push constant 36
@36
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop this 6
@SP
M=M-1
@6
D=A
@THIS
A=M
AD=D+A
@R15
M=D
@SP
A=M
D=M
@R15
A=M
M=D
// push constant 42
@42
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 45
@45
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop that 5
@SP
M=M-1
@5
D=A
@THAT
A=M
AD=D+A
@R15
M=D
@SP
A=M
D=M
@R15
A=M
M=D
// pop that 2
@SP
M=M-1
@2
D=A
@THAT
A=M
AD=D+A
@R15
M=D
@SP
A=M
D=M
@R15
A=M
M=D
// push constant 510
@510
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop temp 6
@SP
M=M-1
@SP
A=M
D=M
@R11
M=D
// push local 0
@LCL
AD=M
D=M
@SP
A=M
M=D
@SP
M=M+1
// push that 5
@5
D=A
@THAT
A=M
AD=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
// add
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
A=M
D=D+A
@SP
A=M
M=D
@SP
M=M+1
// push argument 1
@1
D=A
@ARG
A=M
AD=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
// sub
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
A=M
D=A-D
@SP
A=M
M=D
@SP
M=M+1
// push this 6
@6
D=A
@THIS
A=M
AD=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
// push this 6
@6
D=A
@THIS
A=M
AD=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
// add
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
A=M
D=D+A
@SP
A=M
M=D
@SP
M=M+1
// sub
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
A=M
D=A-D
@SP
A=M
M=D
@SP
M=M+1
// push temp 6
@R11
D=M
@SP
A=M
M=D
@SP
M=M+1
// add
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
A=M
D=D+A
@SP
A=M
M=D
@SP
M=M+1
```