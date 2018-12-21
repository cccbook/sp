	.file	"hello.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.comm	_t0, 4, 2
	.section .rdata,"dr"
LC0:
	.ascii "Hello!\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	call	___main
	movl	$LC0, (%esp)
	call	_puts
	movl	$0, %eax
	leave
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
	.def	_puts;	.scl	2;	.type	32;	.endef
