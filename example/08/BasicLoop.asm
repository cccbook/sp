// init
@SP
M=256
// push constant 0    
@0
D=A
@SP
A=M
M=D
// pop local 0        // initialize sum = 0
@SP
A=M
D=M
@R0
M=D
// label LOOP_START
label LOOP_START
// push argument 0    
@1
D=A
@0
AD=D+A
D=M
@SP
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
A=M
D=M
@R0
M=D
// push argument 0
@1
D=A
@0
AD=D+A
D=M
@SP
A=M
M=D
// push constant 1
@1
D=A
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
// pop argument 0     // counter--
@SP
A=M
D=M
@R0
M=D
// push argument 0
@1
D=A
@0
AD=D+A
D=M
@SP
A=M
M=D
// if-goto LOOP_START // If counter > 0, goto LOOP_START
@SP
M=M-1
@SP
A=M
D=M
@LOOP_START
D; JNE
// push local 0
@1
D=A
@0
AD=D+A
D=M
@SP
A=M
M=D
