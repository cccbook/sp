// init
@SP
M=256
// push constant 10
@10
D=A
@SP
A=M
M=D
// pop local 0
@SP
A=M
D=M
@R0
M=D
// push constant 21
@21
D=A
@SP
A=M
M=D
// push constant 22
@22
D=A
@SP
A=M
M=D
// pop argument 2
@SP
A=M
D=M
@R2
M=D
// pop argument 1
@SP
A=M
D=M
@R1
M=D
// push constant 36
@36
D=A
@SP
A=M
M=D
// pop this 6
@SP
A=M
D=M
@R6
M=D
// push constant 42
@42
D=A
@SP
A=M
M=D
// push constant 45
@45
D=A
@SP
A=M
M=D
// pop that 5
@SP
A=M
D=M
@R5
M=D
// pop that 2
@SP
A=M
D=M
@R2
M=D
// push constant 510
@510
D=A
@SP
A=M
M=D
// pop temp 6
@1
D=A
@6
AD=D+A
@R15
M=D
@SP
A=M
D=M
@R15
A=M
M=D
// push local 0
@1
D=A
@0
AD=D+A
D=M
@SP
A=M
M=D
// push that 5
@1
D=A
@5
AD=D+A
D=M
@SP
A=M
M=D
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
@1
AD=D+A
D=M
@SP
A=M
M=D
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
@1
D=A
@6
AD=D+A
D=M
@SP
A=M
M=D
// push this 6
@1
D=A
@6
AD=D+A
D=M
@SP
A=M
M=D
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
@R6
D=M
@SP
A=M
M=D
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
