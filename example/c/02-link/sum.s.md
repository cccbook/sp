	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_sum
	.p2align	4, 0x90
_sum:                                   ## @sum
	.cfi_startproc
## BB#0:
	pushq	%rbp ## 儲存上一層函數的框架暫存器
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp  ## 儲存返回點 (rsp 應該是連結暫存器，在 call 時被放入返回位址)
Lcfi2:
	.cfi_def_cfa_register %rbp
	movl	%edi,n
	movl	$0, s  ## s=0
	movl	$0, i  ## i=0
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	i, %eax ## eax = i
	cmpl	n, %eax ## i cmp n
	jg	LBB0_4    ## if > goto LBB0_4
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	s, %eax ## eax = s
	addl	i, %eax ## eax = eax + i
	movl	%eax, s ## s = eax
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	i, %eax  ## eax = i
	addl	$1, %eax ## eax++
	movl	%eax, i  ## i = eax     // i++
	jmp	LBB0_1
LBB0_4:
	movl	s, %eax  ## eax = s
	popq	%rbp     
	retq           ## return s
	.cfi_endproc


.subsections_via_symbols
