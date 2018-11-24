	.file	"f2.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "y=%d\12\0"
	.text
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	call	__alloca
	call	___main
	movl	$1, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, (%esp)
	call	_f1
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	$1, %eax
	leave
	ret
.globl _f1
	.def	_f1;	.scl	2;	.type	32;	.endef
_f1:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	leal	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_f2
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	addl	-4(%ebp), %eax
	leave
	ret
.globl _f2
	.def	_f2;	.scl	2;	.type	32;	.endef
_f2:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	addl	$5, %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	leave
	ret
	.def	_f2;	.scl	3;	.type	32;	.endef
	.def	_printf;	.scl	3;	.type	32;	.endef
	.def	_f1;	.scl	3;	.type	32;	.endef
