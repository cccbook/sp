	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_sum
	.p2align	4, 0x90
_sum:                                   ## @sum
	.cfi_startproc
## BB#0:
	pushq	%rbp          ## 儲存上一層函數的框架暫存器
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp    ## 儲存返回點 (rsp 應該是連結暫存器，在 call 入返回位址)
Lcfi2:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	$0, -8(%rbp)  ## s=0
	movl	$0, -12(%rbp) ## i=0
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-12(%rbp), %eax ## eax = i
	cmpl	-4(%rbp), %eax  ## cmp n i
	jg	LBB0_4            ## if n > i goto LBB0_4
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	-8(%rbp), %eax  ## eax = s
	addl	-12(%rbp), %eax ## eax = eax + i
	movl	%eax, -8(%rbp)  ## s = eax
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	-12(%rbp), %eax ## eax = i
	addl	$1, %eax        ## eax ++
	movl	%eax, -12(%rbp) ## i = eax
	jmp	LBB0_1            ## goto LBB0_1
LBB0_4:
	movl	-8(%rbp), %eax  ## eax = s
	popq	%rbp            ## 還原上一層的框架暫存器
	retq                  ## 返回
	.cfi_endproc


.subsections_via_symbols
