	.file	"StackFunc.c"
	.text
.globl _push
	.def	_push;	.scl	2;	.type	32;	.endef
_push:
	pushl	%ebp
	movl	%esp, %ebp
	movl	_top, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%eax, _stack(,%edx,4)
	incl	_top
	popl	%ebp
	ret
.globl _pop
	.def	_pop;	.scl	2;	.type	32;	.endef
_pop:
	pushl	%ebp
	movl	%esp, %ebp
	decl	_top
	movl	_top, %eax
	movl	_stack(,%eax,4), %eax
	popl	%ebp
	ret
