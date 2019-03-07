	.file	"optimize.c"
	.text
.globl _f
	.def	_f;	.scl	2;	.type	32;	.endef
_f:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$3, -4(%ebp)
	movl	$4, -8(%ebp)
	movl	-8(%ebp), %eax
	addl	-4(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-8(%ebp), %eax
	addl	-4(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	addl	-12(%ebp), %eax
	leave
	ret
