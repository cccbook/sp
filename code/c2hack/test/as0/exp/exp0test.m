// t0=3
@3
D=A
@t0
M=D
// t1=5
@5
D=A
@t1
M=D
// t2=4
@4
D=A
@t2
M=D
// t3=t1-t2
@t1
D=M
@t2
D=D-M
@t3
M=D
// t4=t0+t3
@t0
D=M
@t3
D=D+M
@t4
M=D
