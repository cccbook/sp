	.file	"jitCall.c"
	.text
	.globl	addCode
	.text
	.align 32
addCode:
	.byte	85
	.byte	72
	.byte	-119
	.byte	-27
	.byte	-119
	.byte	77
	.byte	16
	.byte	-119
	.byte	85
	.byte	24
	.byte	-117
	.byte	85
	.byte	16
	.byte	-117
	.byte	69
	.byte	24
	.byte	1
	.byte	-48
	.byte	93
	.byte	-61
	.byte	-112
	.byte	-112
	.byte	-112
	.byte	-112
	.byte	-112
	.byte	-112
	.byte	-112
	.byte	-112
	.byte	-112
	.byte	-112
	.byte	-112
	.byte	-112
	.comm	add, 8, 3
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "add(5, 8)=%d\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	movl	$32, -4(%rbp)
	movl	-4(%rbp), %eax
	cltq
	movq	%rax, %rcx
	call	malloc
	movq	%rax, -16(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %r8
	leaq	addCode(%rip), %rdx
	movq	%rax, %rcx
	call	memcpy
	movq	-16(%rbp), %rdx
	leaq	add(%rip), %rax
	movq	%rdx, (%rax)
	leaq	add(%rip), %rax
	movq	(%rax), %rax
	movl	$8, %edx
	movl	$3, %ecx
	call	*%rax
	movl	%eax, %edx
	leaq	.LC0(%rip), %rcx
	call	printf
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 7.3.0"
	.def	malloc;	.scl	2;	.type	32;	.endef
	.def	memcpy;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
