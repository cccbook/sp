	.file	"fib.c"
	.text
	.globl	_fib
	.def	_fib;	.scl	2;	.type	32;	.endef
_fib:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	cmpl	$1, 8(%ebp)
	jg	L2
	movl	$1, %eax
	jmp	L3
L2:
	movl	8(%ebp), %eax
	subl	$1, %eax
	movl	%eax, (%esp)
	call	_fib
	movl	%eax, %ebx
	movl	8(%ebp), %eax
	subl	$2, %eax
	movl	%eax, (%esp)
	call	_fib
	addl	%ebx, %eax
L3:
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
