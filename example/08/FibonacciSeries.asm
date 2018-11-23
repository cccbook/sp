// init
@256
D=A
@RSP
M=D
@LABEL1
D=A
@SP
A=M
M=D
@R1
D=M
@SP
A=M
M=D
@R2
D=M
@SP
A=M
M=D
@R3
D=M
@SP
A=M
M=D
@R4
D=M
@SP
A=M
M=D
@5
D=A
@R0
AD=A-D
@R2
M=D
@R0
D=M
@R1
M=D
@Sys.init
0; JMP
label LABEL1
// push argument 1
@1
D=A
@argument
A=M
AD=D+A
D=M
@SP
A=M
M=D
// pop pointer 1           // that = argument[1]
@SP
A=M
D=M
@R1
M=D
// push constant 0
@0
D=A
@SP
A=M
M=D
// pop that 0              // first element = 0
@0
D=A
@that
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
// push constant 1
@1
D=A
@SP
A=M
M=D
// pop that 1              // second element = 1
@1
D=A
@that
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
// push argument 0
@0
D=A
@argument
A=M
AD=D+A
D=M
@SP
A=M
M=D
// push constant 2
@2
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
// pop argument 0          // num_of_elements -= 2 (first 2 elements are set)
@0
D=A
@argument
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
// label MAIN_LOOP_START
label MAIN_LOOP_START
// push argument 0
@0
D=A
@argument
A=M
AD=D+A
D=M
@SP
A=M
M=D
// if-goto COMPUTE_ELEMENT // if num_of_elements > 0, goto COMPUTE_ELEMENT
@SP
M=M-1
@SP
A=M
D=M
@COMPUTE_ELEMENT
D; JNE
// goto END_PROGRAM        // otherwise, goto END_PROGRAM
@END_PROGRAM
0; JMP
@SP
M=M-1
@SP
A=M
D=M
@END_PROGRAM
D; JNE
// label COMPUTE_ELEMENT
label COMPUTE_ELEMENT
// push that 0
@0
D=A
@that
A=M
AD=D+A
D=M
@SP
A=M
M=D
// push that 1
@1
D=A
@that
A=M
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
// pop that 2              // that[2] = that[0] + that[1]
@2
D=A
@that
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
// push pointer 1
@R31
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
// pop pointer 1           // that += 1
@SP
A=M
D=M
@R1
M=D
// push argument 0
@0
D=A
@argument
A=M
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
// pop argument 0          // num_of_elements--
@0
D=A
@argument
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
// goto MAIN_LOOP_START
@MAIN_LOOP_START
0; JMP
@SP
M=M-1
@SP
A=M
D=M
@MAIN_LOOP_START
D; JNE
// label END_PROGRAM
label END_PROGRAM
