.globl _f1
	.def	_f1;	.scl	2;	.type	32;	.endef
.data
t: .long 0
b: .long 0
.text
_f1:
	leal	t, %eax
	movl	%eax, (%esp)
	call	_f2
	movl	%eax, b
	movl	b, %eax
	addl	b, %eax
	ret
.globl _f2
	.def	_f2;	.scl	2;	.type	32;	.endef
.data
p: .long 0
b: .long 0
.text
_f2:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	p, %eax
	movl	(%eax), %eax
	addl	$5, %eax
	ret
	.def	_f2;	.scl	3;	.type	32;	.endef
	.def	_printf;	.scl	3;	.type	32;	.endef
	.def	_f1;	.scl	3;	.type	32;	.endef
