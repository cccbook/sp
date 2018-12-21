// push constant 0    
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop local 0        // initialize sum = 0
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
// label LOOP_START
(LOOP_START)
// push argument 0    
@ARG
AD=M
D=M
@SP
A=M
M=D
@SP
M=M+1
// push local 0
@LCL
AD=M
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
// pop local 0	   // sum = sum + counter
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
// push argument 0
@ARG
AD=M
D=M
@SP
A=M
M=D
@SP
M=M+1
// push constant 1
@1
D=A
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
// pop argument 0     // counter--
@SP
M=M-1
@ARG
AD=M
@R15
M=D
@SP
A=M
D=M
@R15
A=M
M=D
// push argument 0
@ARG
AD=M
D=M
@SP
A=M
M=D
@SP
M=M+1
// if-goto LOOP_START // If counter > 0, goto LOOP_START
@SP
M=M-1
@SP
A=M
D=M
@LOOP_START
D;JNE
// push local 0
@LCL
AD=M
D=M
@SP
A=M
M=D
@SP
M=M+1
