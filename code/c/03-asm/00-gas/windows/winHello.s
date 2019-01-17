	.file	"winHello.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "Hello, world!\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$52, %esp
	call	___main
	movl	$LC0, -12(%ebp)
	movl	$-11, (%esp)
	call	_GetStdHandle@4
	subl	$4, %esp
	movl	%eax, -16(%ebp)
	movl	$0, 16(%esp)
	leal	-20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$14, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_WriteFile@20
	subl	$20, %esp
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	leave
	leal	-4(%ecx), %esp
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
	.def	_GetStdHandle@4;	.scl	2;	.type	32;	.endef
	.def	_WriteFile@20;	.scl	2;	.type	32;	.endef
