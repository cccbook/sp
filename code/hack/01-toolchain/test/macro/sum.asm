@main  
0;JMP  
  
(msg) "sum=", 0  
(i) 1  
(sum) 0  
  
(main)  
  
(loop)  
// if i>10 goto exit  
@i  
D=M  
@10  
D=D-A  
@exit  
D;JGT  
// sum = sum + i  
@sum  
D=M  
@i  
D=D+M  
@sum  
M=D  
// i = i + 1  
@1  
D=A  
@i  
M=M+1  
// goto loop  
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
