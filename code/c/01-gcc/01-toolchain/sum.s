	.file	"sum.c"
	.text
	.globl	_sum
	.def	_sum;	.scl	2;	.type	32;	.endef
_sum:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)
	jmp	L2
L3:
	movl	-8(%ebp), %eax
	addl	%eax, -4(%ebp)
	addl	$1, -8(%ebp)
L2:
	movl	-8(%ebp), %eax
	cmpl	8(%ebp), %eax
	jle	L3
	movl	-4(%ebp), %eax
	leave
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "sum(10)=%d\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	call	___main
	movl	$10, (%esp)
	call	_sum
	movl	%eax, 28(%esp)
	movl	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	$0, %eax
	leave
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
