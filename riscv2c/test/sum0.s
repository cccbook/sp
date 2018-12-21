# extern   printf                     # printf                     #         
# file     "sum.c"                    # "sum.c"                    #         
	.file "sum.c"
	.def	___main;	.scl	2;	.type	32;	.endef
# str      _Str0    "i=%d s=%d n=%d\n"          # _Str0    "i=%d s=%d n=%d\n"          #         
	.section .rdata,"dr"
_Str0:
	.ascii "i=%d s=%d n=%d\n\0"
	.text
# str      _Str3    "i=%d s=%d\n"          # _Str3    "i=%d s=%d\n"          #         
	.section .rdata,"dr"
_Str3:
	.ascii "i=%d s=%d\n\0"
	.text
# str      _Str4    "sum(10)=%d\n"          # _Str4    "sum(10)=%d\n"          #         
	.section .rdata,"dr"
_Str4:
	.ascii "sum(10)=%d\n\0"
	.text
# function sum      int               # sum      int               # 6       
	.text
	.globl	_sum
	.def	sum;	.scl	2;	.type	32;	.endef
_sum:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
# param    n        int               # n        int               # P0      
# local    s        int               # s        int               # L0      
# =        s        0                 # L0       0                 #         
	movl	$0, %ebx
	movl	%ebx, -4(%ebp)
# local    i        int               # i        int               # L1      
# =        i        1                 # L1       1                 #         
	movl	$1, %ebx
	movl	%ebx, -8(%ebp)
# arg      _Str0                      # $_Str0                     # 0       
	movl $_Str0, %eax
	movl %eax, 0(%esp)
# arg      i                          # L1                         # 1       
	movl -8(%ebp), %eax
	movl %eax, 4(%esp)
# arg      s                          # L0                         # 2       
	movl -4(%ebp), %eax
	movl %eax, 8(%esp)
# arg      n                          # P0                         # 3       
	movl 8(%ebp), %eax
	movl %eax, 12(%esp)
# local    t0                         # t0                         # L2      
# call     t0       printf            # L2       _printf           #         
	call _printf
	movl %eax, -12(%ebp)
# label    _WBEGIN1                   # _WBEGIN1                   #         
_WBEGIN1:
# <=       t0       i        n        # L2       L1       P0       #         
	movl -8(%ebp), %eax
	movl 8(%ebp), %ebx
	cmpl %ebx, %eax
	setle %al
	movsbl	%al, %eax
	movl	%eax, -12(%ebp)
# jz       _WEND2   t0                # _WEND2   L2                #         
	movl	-12(%ebp), %eax
	cmpl	$0, %eax
	je	_WEND2
# local    t1                         # t1                         # L3      
# +        t1       s        i        # L3       L0       L1       #         
	movl	-4(%ebp), %eax
	addl	-8(%ebp), %eax
	movl	%eax, -16(%ebp)
# =        s        t1                # L0       L3                #         
	movl	-16(%ebp), %ebx
	movl	%ebx, -4(%ebp)
# arg      _Str3                      # $_Str3                     # 0       
	movl $_Str3, %eax
	movl %eax, 0(%esp)
# arg      i                          # L1                         # 1       
	movl -8(%ebp), %eax
	movl %eax, 4(%esp)
# arg      s                          # L0                         # 2       
	movl -4(%ebp), %eax
	movl %eax, 8(%esp)
# call     t0       printf            # L2       _printf           #         
	call _printf
	movl %eax, -12(%ebp)
# +        t1       i        1        # L3       L1       1        #         
	movl	-8(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
# =        i        t1                # L1       L3                #         
	movl	-16(%ebp), %ebx
	movl	%ebx, -8(%ebp)
# jmp      _WBEGIN1                   # _WBEGIN1                   #         
	jmp	_WBEGIN1
# label    _WEND2                     # _WEND2                     #         
_WEND2:
# return   s                          # L0                         #         
	movl -4(%ebp), %eax
	leave
	ret
# -function sum                        # sum                        #         
	movl $0, %eax
	leave
	ret
# function main     int               # main     int               # 4       
	.text
	.globl	_main
	.def	main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	call	___main
# arg      10                         # 10                         # 0       
	movl $10, %eax
	movl %eax, 0(%esp)
# local    t0                         # t0                         # L0      
# call     t0       sum               # L0       _sum              #         
	call _sum
	movl %eax, -4(%ebp)
# arg      _Str4                      # $_Str4                     # 0       
	movl $_Str4, %eax
	movl %eax, 0(%esp)
# arg      t0                         # L0                         # 1       
	movl -4(%ebp), %eax
	movl %eax, 4(%esp)
# local    t1                         # t1                         # L1      
# call     t1       printf            # L1       _printf           #         
	call _printf
	movl %eax, -8(%ebp)
# -function main                       # main                       #         
	movl $0, %eax
	leave
	ret
# -file    "sum.c"                    # "sum.c"                    #         
	.ident	"c0c: 0.0.1"
	.def	_puts;	.scl	2;	.type	32;	.endef
