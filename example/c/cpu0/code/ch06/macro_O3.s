	.file	"macro.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "max(3,5)=%d\12\0"
LC1:
	.ascii "min(3,5)=%d\12\0"
	.text
	.p2align 4,,15
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	$16, %eax
	movl	%esp, %ebp
	subl	$8, %esp
	andl	$-16, %esp
	call	__alloca
	call	___main
	movl	$LC0, (%esp)
	movl	$5, %edx
	movl	%edx, 4(%esp)
	call	_printf
	movl	$LC1, (%esp)
	movl	$3, %eax
	movl	%eax, 4(%esp)
	call	_printf
	leave
	ret
	.def	_printf;	.scl	3;	.type	32;	.endef
