	.file	"sum.c"
	.text
.globl _sum
	.def	_sum;	.scl	2;	.type	32;	.endef
_sum:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$0, -4(%ebp)
	movl	$1, -8(%ebp)
L2:
	movl	-8(%ebp), %eax
	cmpl	8(%ebp), %eax
	jg	L3
	movl	-8(%ebp), %eax
	leal	-4(%ebp), %edx
	addl	%eax, (%edx)
	leal	-8(%ebp), %eax
	incl	(%eax)
	jmp	L2
L3:
	movl	-4(%ebp), %eax
	leave
	ret
