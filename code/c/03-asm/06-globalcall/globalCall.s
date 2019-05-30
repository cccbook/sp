	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_add
	.p2align	4, 0x90
_add:                                   ## @add
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	movl	_a(%rip), %eax
	addl	_b(%rip), %eax
	movl	%eax, _c(%rip)
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi3:
	.cfi_def_cfa_offset 16
Lcfi4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi5:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	callq	_add
	leaq	L_.str(%rip), %rdi
	movl	_c(%rip), %esi
	movb	$0, %al
	callq	_printf
	xorl	%esi, %esi
	movl	%eax, -8(%rbp)          ## 4-byte Spill
	movl	%esi, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__DATA,__data
	.globl	_a                      ## @a
	.p2align	2
_a:
	.long	5                       ## 0x5

	.globl	_b                      ## @b
	.p2align	2
_b:
	.long	8                       ## 0x8

	.globl	_c                      ## @c
	.p2align	2
_c:
	.long	1                       ## 0x1

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"add(5, 8)=%d\n"


.subsections_via_symbols
