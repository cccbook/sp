// init
@SP
M=256
// push constant 3030
@3030
D=A
@SP
A=M
M=D
// pop pointer 0
@1
D=A
@0
AD=D+A
@R15
M=D
@SP
A=M
D=M
@R15
A=M
M=D
// push constant 3040
@3040
D=A
@SP
A=M
M=D
// pop pointer 1
@1
D=A
@1
AD=D+A
@R15
M=D
@SP
A=M
D=M
@R15
A=M
M=D
// push constant 32
@32
D=A
@SP
A=M
M=D
// pop this 2
@SP
A=M
D=M
@R2
M=D
// push constant 46
@46
D=A
@SP
A=M
M=D
// pop that 6
@SP
A=M
D=M
@R6
M=D
// push pointer 0
@R0
D=M
@SP
A=M
M=D
// push pointer 1
@R1
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
// push this 2
@1
D=A
@2
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
// push that 6
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
