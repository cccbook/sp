@main  
0;JMP  
  
(C4) 4.0  
(PI) 3.14159  
  
(main)  
// .fset PI  
@PI
D=A
@17
swi
// .fput  
@18
swi
// .fadd PI  
@PI
D=A
@19
swi
// .fput  
@18
swi
// .fmul C4  
@C4
D=A
@21
swi
// .fput  
@18
swi
