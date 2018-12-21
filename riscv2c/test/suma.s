	.file	"suma.c"
	.text
	.globl	_total
	.def	_total;	.scl	2;	.type	32;	.endef
_total:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)
	jmp	L2
L3:
	movl	-8(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	addl	%eax, -4(%ebp)
L2:
	movl	-8(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L3
	movl	-4(%ebp), %eax
	leave
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
