@main  
0;JMP  
  
(msg) "sum=", 0  
(i) 1  
(sum) 0  
(c1) 1  
(c10) 10  
  
(main)  
  
// .= sum 0  
@sum
D=M
@0
M=D
// .= i 1  
@i
D=M
@1
M=D
  
(loop)  
// .op e1 = i > c10  
@i
D=M
@c10
D=D>M
@e1
M=D
// .if e1 goto exit  
@e1
D=M
@exit
D;JNE
// .op sum = sum + i  
@sum
D=M
@i
D=D+M
@sum
M=D
// .op i = i + c1  
@i
D=M
@c1
D=D+M
@i
M=D
// .goto loop  
@loop
0;JMP
  
(exit)  
  
// .sput msg  
@msg
D=A
@3
swi
// .iput sum  
@sum
D=M
@0
swi
