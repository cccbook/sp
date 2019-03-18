@main
0;JMP

(C4) 4.0
(PI) 3.14159

(main)
@PI
D=A
@16 // get F(PI)
swi
@18 // putf F
swi
@PI
D=A
@19 // fadd F , PI
swi
@18 // putf F
swi
@C4
D=A
@21 // fmul F, 2
swi
@18 // putf F
swi
