	.file	"sumg.c"
	.comm	_s, 4, 2
	.comm	_n, 4, 2
	.comm	_i, 4, 2
	.text
	.globl	_sum
	.def	_sum;	.scl	2;	.type	32;	.endef
_sum:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, _s
	movl	$1, _i
	jmp	L2
L3:
	movl	_s, %edx
	movl	_i, %eax
	addl	%edx, %eax
	movl	%eax, _s
	movl	_i, %eax
	addl	$1, %eax
	movl	%eax, _i
L2:
	movl	_i, %edx
	movl	_n, %eax
	cmpl	%eax, %edx # n-i
	jle	L3 # n-i <= 0
	movl	_s, %eax
	popl	%ebp
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "s=%d\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	call	___main
	movl	$10, _n
	call	_sum
	movl	%eax, _s
	movl	_s, %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	$0, %eax
	leave
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
