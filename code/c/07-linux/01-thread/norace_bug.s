	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_inc
	.p2align	4, 0x90
_inc:                                   ## @inc
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
	subq	$16, %rsp
	movl	$0, -4(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$100000, -4(%rbp)       ## imm = 0x186A0
	jge	LBB0_4
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	leaq	_mutex1(%rip), %rdi
	callq	_pthread_mutex_lock
	leaq	_mutex1(%rip), %rdi
	movl	_counter(%rip), %ecx
	addl	$1, %ecx
	movl	%ecx, _counter(%rip)
	movl	%eax, -8(%rbp)          ## 4-byte Spill
	callq	_pthread_mutex_unlock
	movl	%eax, -12(%rbp)         ## 4-byte Spill
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	-4(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -4(%rbp)
	jmp	LBB0_1
LBB0_4:
	xorl	%eax, %eax
                                        ## kill: %RAX<def> %EAX<kill>
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_dec
	.p2align	4, 0x90
_dec:                                   ## @dec
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
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$100000, -4(%rbp)       ## imm = 0x186A0
	jge	LBB1_4
## BB#2:                                ##   in Loop: Header=BB1_1 Depth=1
	leaq	_mutex1(%rip), %rdi
	callq	_pthread_mutex_lock
	leaq	_mutex1(%rip), %rdi
	movl	_counter(%rip), %ecx
	subl	$1, %ecx
	movl	%ecx, _counter(%rip)
	movl	%eax, -8(%rbp)          ## 4-byte Spill
	callq	_pthread_mutex_unlock
	movl	%eax, -12(%rbp)         ## 4-byte Spill
## BB#3:                                ##   in Loop: Header=BB1_1 Depth=1
	movl	-4(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -4(%rbp)
	jmp	LBB1_1
LBB1_4:
	xorl	%eax, %eax
                                        ## kill: %RAX<def> %EAX<kill>
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi6:
	.cfi_def_cfa_offset 16
Lcfi7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi8:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	leaq	-8(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %ecx
	leaq	_inc(%rip), %rdx
	movq	%rcx, %rsi
	callq	_pthread_create
	leaq	-16(%rbp), %rdi
	xorl	%r8d, %r8d
	movl	%r8d, %ecx
	leaq	_dec(%rip), %rdx
	movq	%rcx, %rsi
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	callq	_pthread_create
	leaq	L_.str(%rip), %rdi
	movl	_counter(%rip), %esi
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	xorl	%esi, %esi
                                        ## kill: %RSI<def> %ESI<kill>
	movq	-8(%rbp), %rdi
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	callq	_pthread_join
	xorl	%r8d, %r8d
	movl	%r8d, %esi
	movq	-16(%rbp), %rdi
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	callq	_pthread_join
	xorl	%r8d, %r8d
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	movl	%r8d, %eax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__DATA,__data
	.globl	_mutex1                 ## @mutex1
	.p2align	3
_mutex1:
	.quad	850045863               ## 0x32aaaba7
	.space	56

	.globl	_counter                ## @counter
.zerofill __DATA,__common,_counter,4,2
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"counter=%d\n"


.subsections_via_symbols
