# HackCPU 的延伸擴展

## 1. 加入常用運算

D*A
D/A
D%A
D << A
D >> A
D < A    // 小於
D <= A
D > A
D >= A
D == A
D != A
D ^ A

## 2. 納入指令記憶體的存取指令

D = D + I    其中 I 代表指令記憶體 (原本只能 D=D+M)

這樣就可以在指令記憶體裡塞入常數與字串。

## 3. 加入浮點數 FPU

採用記憶體映射的方式，將浮點數映射到 Keyboard 24576 的後面。

如此就可以呼叫 fadd, fsub, fmul, fdiv 等指令。

fadd: f1 = f1 + f2
fsub: f1 = f1 - f2
fmul: f1 = f1 * f2
fdiv: f1 = f1 / f2

float 的初始值可以存在 IM 記憶體裡。




