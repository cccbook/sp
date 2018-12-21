# c0c 組譯器

## 中間碼轉組合語言

所有的臨時變數都只使用一次 (Single Assignment)，所以都不用保留 (或在組合語言中宣告變數)，只要放在某個暫存器中介，用掉就好了！

例如以下範例中的 t0 ... t7 通通都可以放在 eax 或 R1 中介掉，所以不用保留。

```
    function   sum        int                  
    param      n          int                  
    local      s          int                  
    local      i          int                  
    =          t0         0                    eax = 0
    =          s          t0                   s = eax
    =          t1         1                    eax = 1
    =          i          t1                   i = eax
(WBEGIN2)
    <=         t4         i          n         eax = (i <= n)
    jnz        WEND3      t4                   jnz WEND3 eax
    +          t5         s          i         eax = s + i
    =          s          t5                   s = eax
    =          t6         1                    eax = 1
    +          t7         i          t6        eax = i + eax
    =          i          t7                   i = eax
    jmp        WBEGIN2                         
(WEND3)
    return     s                               eax = s
```

範例 asum.p0

```
    function   total      int                  
    param      a          int        *         
    param      size       int                  
    local      s          int                  
    local      i          int                  
    =          t0         0                    eax = 0
    =          s          t0                   s = eax
    =          t1         0                    eax = 0
    =          i          t1                   i = eax
(WBEGIN2)
    <          t4         i          size      eax = (i<size)
    jnz        WEND3      t4                   jnz WEND3 eax
    []         t5         a          i         eax = a[i]    // 這裡要小心，不要覆蓋掉 eax, 否則就應用其他暫存器。
    +          t6         s          t5        eax = s + eax
    =          s          t6                   s = eax
    jmp        WBEGIN2                         
(WEND3)
    return     s                               eax = s

```


## 有 frame 的版本

```
$ ../c0c sump
#include <stdio.h>

int total(int *a, int size) {
  int s = 0, i = 0;
  while (i < size) {
    s = s + *a;
    a ++;
  }
  return s;
}

int main() {
  int total = sum(10);
  printf("sum(10)=%d\n", total);
}

================= lex =================
0001:#          line=1 pos=1 type=Char
0002:include    line=1 pos=8 type=Id
0003:<          line=1 pos=10 type=Char
0004:stdio      line=1 pos=15 type=Id
0005:.          line=1 pos=16 type=Char
0006:h          line=1 pos=17 type=Id
0007:>          line=1 pos=18 type=Char
0008:int        line=3 pos=3 type=Type
0009:total      line=3 pos=9 type=Id
0010:(          line=3 pos=10 type=Char
0011:int        line=3 pos=13 type=Type
0012:*          line=3 pos=15 type=Char
0013:a          line=3 pos=16 type=Id
0014:,          line=3 pos=17 type=Char
0015:int        line=3 pos=21 type=Type
0016:size       line=3 pos=26 type=Id
0017:)          line=3 pos=27 type=Char
0018:{          line=3 pos=29 type=Char
0019:int        line=4 pos=5 type=Type
0020:s          line=4 pos=7 type=Id
0021:=          line=4 pos=9 type=Char
0022:0          line=4 pos=11 type=Number
0023:,          line=4 pos=12 type=Char
0024:i          line=4 pos=14 type=Id
0025:=          line=4 pos=16 type=Char
0026:0          line=4 pos=18 type=Number
0027:;          line=4 pos=19 type=Char
0028:while      line=5 pos=7 type=Id
0029:(          line=5 pos=9 type=Char
0030:i          line=5 pos=10 type=Id
0031:<          line=5 pos=12 type=Char
0032:size       line=5 pos=17 type=Id
0033:)          line=5 pos=18 type=Char
0034:{          line=5 pos=20 type=Char
0035:s          line=6 pos=5 type=Id
0036:=          line=6 pos=7 type=Char
0037:s          line=6 pos=9 type=Id
0038:+          line=6 pos=11 type=Char
0039:*          line=6 pos=13 type=Char
0040:a          line=6 pos=14 type=Id
0041:;          line=6 pos=15 type=Char
0042:a          line=7 pos=5 type=Id
0043:++         line=7 pos=8 type=Char
0044:;          line=7 pos=9 type=Char
0045:}          line=8 pos=3 type=Char
0046:return     line=9 pos=8 type=Id
0047:s          line=9 pos=10 type=Id
0048:;          line=9 pos=11 type=Char
0049:}          line=10 pos=1 type=Char
0050:int        line=12 pos=3 type=Type
0051:main       line=12 pos=8 type=Id
0052:(          line=12 pos=9 type=Char
0053:)          line=12 pos=10 type=Char
0054:{          line=12 pos=12 type=Char
0055:int        line=13 pos=5 type=Type
0056:total      line=13 pos=11 type=Id
0057:=          line=13 pos=13 type=Char
0058:sum        line=13 pos=17 type=Id
0059:(          line=13 pos=18 type=Char
0060:10         line=13 pos=20 type=Number
0061:)          line=13 pos=21 type=Char
0062:;          line=13 pos=22 type=Char
0063:printf     line=14 pos=8 type=Id
0064:(          line=14 pos=9 type=Char
0065:"sum(10)=%d\n" line=14 pos=23 type=Literal
0066:,          line=14 pos=24 type=Char
0067:total      line=14 pos=30 type=Id
0068:)          line=14 pos=31 type=Char
0069:;          line=14 pos=32 type=Char
0070:}          line=15 pos=1 type=Char
============ compile =============
=============vmDump()==============
extern   printf                     # printf
file     "sump.c"                   # "sump.c"
str      _Str2    "sum(10)=%d\n"          # _Str2    "sum(10)=%d\n"
=============vmDump()==============
function total    int               # total    int      4
param    a        int*              # a        int*     P0
param    size     int               # size     int      P1
local    s        int               # s        int      L0
=        s        0                 # L0       0
local    i        int               # i        int      L1
=        i        0                 # L1       0
label    _WBEGIN0                   # _WBEGIN0
local    t0                         # t0                L2
<        t0       i        size     # L2       L1       P1
jz       _WEND1   t0                # _WEND1   L2
+        t0       s        a        # L2       L0       P0
=        s        t0                # L0       L2
++       a                          # P0       int*
jmp      _WBEGIN0                   # _WBEGIN0
label    _WEND1                     # _WEND1
return   s                          # L0
-function total                      # total
function main     int               # main     int      4
local    total    int               # total    int      L0
arg      10                         # 10                0
local    t0                         # t0                L1
call     t0       sum               # L1       ?sum
=        total    t0                # L0       L1
arg      _Str2                      # $_Str2            0
arg      total                      # L0                1
call     t0       printf            # L1       _printf
-function main                       # main
-file    "sump.c"                   # "sump.c"
=============vmToAsm()==============
# extern   printf                     # printf
# file     "sump.c"                   # "sump.c"
# str      _Str2    "sum(10)=%d\n"          # _Str2    "sum(10)=%d\n"
# function total    int               # total    int      4
# param    a        int*              # a        int*     P0
# param    size     int               # size     int      P1
# local    s        int               # s        int      L0
# =        s        0                 # L0       0
# local    i        int               # i        int      L1
# =        i        0                 # L1       0
# label    _WBEGIN0                   # _WBEGIN0
# local    t0                         # t0                L2
# <        t0       i        size     # L2       L1       P1
# jz       _WEND1   t0                # _WEND1   L2
# +        t0       s        a        # L2       L0       P0
# =        s        t0                # L0       L2
# ++       a                          # P0       int*
# jmp      _WBEGIN0                   # _WBEGIN0
# label    _WEND1                     # _WEND1
# return   s                          # L0
# -function total                      # total
# function main     int               # main     int      4
# local    total    int               # total    int      L0
# arg      10                         # 10                0
# local    t0                         # t0                L1
# call     t0       sum               # L1       ?sum
# =        total    t0                # L0       L1
# arg      _Str2                      # $_Str2            0
# arg      total                      # L0                1
# call     t0       printf            # L1       _printf
# -function main                       # main
# -file    "sump.c"                   # "sump.c"
```

組合語言 : suml0.s

```
# extern   printf                     # printf                    
# file     "suml.c"                   # "suml.c"                  
	.file "suml.c"
	.def	___main;	.scl	2;	.type	32;	.endef
# str      _Str0    "i=%d s=%d n=%d\n"          # _Str0    "i=%d s=%d n=%d\n"         
	.section .rdata,"dr"
_Str0:
	.ascii "i=%d s=%d n=%d\n\0"
	.text
# str      _Str3    "i=%d s=%d\n"          # _Str3    "i=%d s=%d\n"         
	.section .rdata,"dr"
_Str3:
	.ascii "i=%d s=%d\n\0"
	.text
# str      _Str4    "sum(10)=%d\n"          # _Str4    "sum(10)=%d\n"         
	.section .rdata,"dr"
_Str4:
	.ascii "sum(10)=%d\n\0"
	.text
# function sum      int               # sum      int      6       
	.text
	.globl	_sum
	.def	sum;	.scl	2;	.type	32;	.endef
_sum:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
# param    n        int               # n        int      P0      
# local    s        int               # s        int      L0      
# =        s        0                 # L0       0                
	movl	$0, %ebx
	movl	%ebx, -4(%ebp)
# local    i        int               # i        int      L1      
# =        i        1                 # L1       1                
	movl	$1, %ebx
	movl	%ebx, -8(%ebp)
# arg      _Str0                      # $_Str0            0       
	movl $_Str0, %eax
	movl %eax, 0(%esp)
# arg      i                          # L1                1       
	movl -8(%ebp), %eax
	movl %eax, 4(%esp)
# arg      s                          # L0                2       
	movl -4(%ebp), %eax
	movl %eax, 8(%esp)
# arg      n                          # P0                3       
	movl 8(%ebp), %eax
	movl %eax, 12(%esp)
# local    t0                         # t0                L2      
# call     t0       printf            # L2       _printf          
	call _printf
	movl %eax, -12(%ebp)
# label    _WBEGIN1                   # _WBEGIN1                  
_WBEGIN1:
# <=       t0       i        n        # L2       L1       P0      
	movl -8(%ebp), %eax
	movl 8(%ebp), %ebx
	cmpl %ebx, %eax
	setle %al
	movsbl	%al, %eax
	movl	%eax, -12(%ebp)
# jz       _WEND2   t0                # _WEND2   L2               
	movl	-12(%ebp), %eax
	cmpl	$0, %eax
	je	_WEND2
# +        t0       s        i        # L2       L0       L1      
	movl	-4(%ebp), %eax
	addl	-8(%ebp), %eax
	movl %eax, -12(%ebp)
# =        s        t0                # L0       L2               
	movl	-12(%ebp), %ebx
	movl	%ebx, -4(%ebp)
# arg      _Str3                      # $_Str3            0       
	movl $_Str3, %eax
	movl %eax, 0(%esp)
# arg      i                          # L1                1       
	movl -8(%ebp), %eax
	movl %eax, 4(%esp)
# arg      s                          # L0                2       
	movl -4(%ebp), %eax
	movl %eax, 8(%esp)
# call     t0       printf            # L2       _printf          
	call _printf
	movl %eax, -12(%ebp)
# +        t0       i        1        # L2       L1       1       
	movl	-8(%ebp), %eax
	addl	$1, %eax
	movl %eax, -12(%ebp)
# =        i        t0                # L1       L2               
	movl	-12(%ebp), %ebx
	movl	%ebx, -8(%ebp)
# jmp      _WBEGIN1                   # _WBEGIN1                  
	jmp	_WBEGIN1
# label    _WEND2                     # _WEND2                    
_WEND2:
# return   s                          # L0                        
	movl -4(%ebp), %eax
	leave
	ret
# -function sum                        # sum                       
	movl $0, %eax
	leave
	ret
# function main     int               # main     int      4       
	.text
	.globl	_main
	.def	main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	call	___main
# local    total    int               # total    int      L0      
# arg      10                         # 10                0       
	movl $10, %eax
	movl %eax, 0(%esp)
# local    t0                         # t0                L1      
# call     t0       sum               # L1       _sum             
	call _sum
	movl %eax, -8(%ebp)
# =        total    t0                # L0       L1               
	movl	-8(%ebp), %ebx
	movl	%ebx, -4(%ebp)
# arg      _Str4                      # $_Str4            0       
	movl $_Str4, %eax
	movl %eax, 0(%esp)
# arg      total                      # L0                1       
	movl -4(%ebp), %eax
	movl %eax, 4(%esp)
# call     t0       printf            # L1       _printf          
	call _printf
	movl %eax, -8(%ebp)
# -function main                       # main                      
	movl $0, %eax
	leave
	ret
# -file    "suml.c"                   # "suml.c"                  
	.ident	"c0c: 0.0.1"
	.def	_puts;	.scl	2;	.type	32;	.endef

```