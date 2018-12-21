# extern   printf                     # printf                     #         
# file     "suma.c"                   # "suma.c"                   #         
	.file "suma.c"
	.def	___main;	.scl	2;	.type	32;	.endef
# function total    int               # total    int               # 5       
	.text
	.globl	_total
	.def	total;	.scl	2;	.type	32;	.endef
_total:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
# param    a        int*              # a        int*              # P0      
# param    size     int               # size     int               # P1      
# local    s        int               # s        int               # L0      
# =        s        0                 # L0       0                 #         
	movl	$0, %ebx
	movl	%ebx, -4(%ebp)
# local    i        int               # i        int               # L1      
# =        i        0                 # L1       0                 #         
	movl	$0, %ebx
	movl	%ebx, -8(%ebp)
# label    _WBEGIN0                   # _WBEGIN0                   #         
_WBEGIN0:
# local    t0                         # t0                         # L2      
# <        t0       i        size     # L2       L1       P1       #         
	movl -8(%ebp), %eax
	movl 12(%ebp), %ebx
	cmpl %ebx, %eax
	setl %al
	movsbl	%al, %eax
	movl	%eax, -12(%ebp)
# jz       _WEND1   t0                # _WEND1   L2                #         
	movl	-12(%ebp), %eax
	cmpl	$0, %eax
	je	_WEND1
# []       t0       a        i        # L2       P0       L1       # int*    
	movl	8(%ebp), %eax
	addl	-8(%ebp), %eax
	shll	$2, %eax
	movl %eax, -12(%ebp)
# local    t1                         # t1                         # L3      
# +        t1       s        t0       # L3       L0       L2       #         
	movl	-4(%ebp), %eax
	addl	-12(%ebp), %eax
	movl %eax, -16(%ebp)
# =        s        t1                # L0       L3                #         
	movl	-16(%ebp), %ebx
	movl	%ebx, -4(%ebp)
# jmp      _WBEGIN0                   # _WBEGIN0                   #         
	jmp	_WBEGIN0
# label    _WEND1                     # _WEND1                     #         
_WEND1:
# return   s                          # L0                         #         
	movl -4(%ebp), %eax
	leave
	ret
# -function total                      # total                      #         
	movl $0, %eax
	leave
	ret
# -file    "suma.c"                   # "suma.c"                   #         
	.ident	"c0c: 0.0.1"
	.def	_puts;	.scl	2;	.type	32;	.endef
