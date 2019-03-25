@main
0;JMP

(msg) "sum=", 0
(i) 1
(sum) 0
(c1) 1
(c10) 10

(main)

.= sum 0
.= i 1

(loop)
.op e1 = i > c10
.if e1 goto exit
.op sum = sum + i
.op i = i + c1
.goto loop

(exit)

.sput msg
.iput sum
