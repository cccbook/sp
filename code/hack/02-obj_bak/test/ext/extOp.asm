@main
0;JMP

(str) "hello!", 0
(f1) 3.14159
(i1) 47
// (cstr) "中文字串", 0

(main)
@3
D=A
@5
D=D*A
@0
M=D
D=D*M
@0
(label)
D=D*A
@str
D=A
@2
swi