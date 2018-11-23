// init
@SP
M=256
// push constant 7
@7
D=A
@SP
A=M
M=D
// push constant 8
@8
D=A
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
