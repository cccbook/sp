# file "sumg.c"  
	.file "sumg.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.comm	_t0, 4, 2
	.comm	_t1, 4, 2
	.comm	_t2, 4, 2
	.comm	_t3, 4, 2
	.comm	_t4, 4, 2
	.comm	_t5, 4, 2
	.comm	_t6, 4, 2
	.comm	_t7, 4, 2
	.comm	_t8, 4, 2
# global s int 
	.comm	_s, 4, 2
# global n int 
	.comm	_n, 4, 2
# global i int 
	.comm	_i, 4, 2
# str $S2 "s=%d\n" 
	.section .rdata,"dr"
S2:
	.ascii "s=%d\n\0"
S3:
	.ascii "i=%d n=%d\n\0"
S4:
	.ascii "t0=%d\n\0"
	.text
# function sum int 2
	.text
	.globl	_sum
	.def	_sum;	.scl	2;	.type	32;	.endef
_sum:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$48, %esp
# = s 0 
	movl	$0, %ebx
	movl	%ebx, _s
# = i 1 
	movl	$1, %ebx
	movl	%ebx, _i
# label WBEGIN0  
_WBEGIN0:
# local t0  0
  # do nothing
# arg $S3  
	movl $S3, %eax
	movl %eax, 0(%esp)
# arg i  
	movl _i, %eax
	movl %eax, 4(%esp)
# arg s  
	movl _n, %eax
	movl %eax, 8(%esp)
# call t0 printf 
	call _printf
# <= t0 i n
	movl _i, %eax
	movl _n, %ebx
	cmpl %ebx, %eax   # eax-ebx : i-n
	setle %al       # i-n <=0 ?
	movsbl	%al, %eax
	movl	%eax, _t0

# arg $S4  
	movl $S4, %eax
	movl %eax, 0(%esp)
# arg t0  
	movl _t0, %eax
	movl %eax, 4(%esp)
# call t0 printf 
	call _printf

# jnz WEND1 t0 

	movl	_t0, %eax
	cmpl	$0, %eax
	jz	_WEND1
# + t0 s i
	movl	_s, %eax
	addl	_i, %eax
	movl %eax, _t0
# = s t0 
	movl	_t0, %ebx
	movl	%ebx, _s
# + t0 i 1
	movl	_i, %eax
	addl	$1, %eax
	movl %eax, _t0
# = i t0 
	movl	_t0, %ebx
	movl	%ebx, _i
# jmp WBEGIN0  
	jmp	_WBEGIN0
# label WEND1  
_WEND1:
# return s  
	movl _s, %eax
	leave
	ret
# -function sum  
	movl $0, %eax
	leave
	ret
# function main int 2
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	call	___main
# = n 10 
	movl	$10, %ebx
	movl	%ebx, _n
# local t0  0
  # do nothing
# call t0 sum 
	call _sum
	movl %eax, _t0
# = s t0 
	movl	_t0, %ebx
	movl	%ebx, _s
# arg $S2  
	movl $S2, %eax
	movl %eax, 0(%esp)
# arg s  
	movl _s, %eax
	movl %eax, 4(%esp)
# call t0 printf 
	call _printf
	movl %eax, _t0
# -function main  
	movl $0, %eax
	leave
	ret
# -file "sumg.c"  
	.ident	"c0c: 0.0.1"
	.def	_puts;	.scl	2;	.type	32;	.endef
