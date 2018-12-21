	.file	"opall.c"
 # GNU C11 (tdm-1) version 5.1.0 (mingw32)
 #	compiled by GNU C version 5.1.0, GMP version 4.3.2, MPFR version 2.4.2, MPC version 0.8.2
 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: 
 # -iprefix C:/Program Files (x86)/CodeBlocks/MinGW/bin/../lib/gcc/mingw32/5.1.0/
 # -D_REENTRANT opall.c -mtune=generic -march=pentiumpro
 # -auxbase-strip opall.s -fverbose-asm
 # options enabled:  -faggressive-loop-optimizations
 # -fasynchronous-unwind-tables -fauto-inc-dec -fchkp-check-incomplete-type
 # -fchkp-check-read -fchkp-check-write -fchkp-instrument-calls
 # -fchkp-narrow-bounds -fchkp-optimize -fchkp-store-bounds
 # -fchkp-use-static-bounds -fchkp-use-static-const-bounds
 # -fchkp-use-wrappers -fcommon -fdelete-null-pointer-checks
 # -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-types
 # -ffunction-cse -fgcse-lm -fgnu-runtime -fgnu-unique -fident
 # -finline-atomics -fira-hoist-pressure -fira-share-save-slots
 # -fira-share-spill-slots -fivopts -fkeep-inline-dllexport
 # -fkeep-static-consts -fleading-underscore -flifetime-dse
 # -flto-odr-type-merging -fmath-errno -fmerge-debug-strings -fpeephole
 # -fprefetch-loop-arrays -freg-struct-return
 # -fsched-critical-path-heuristic -fsched-dep-count-heuristic
 # -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
 # -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
 # -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
 # -fset-stack-executable -fshow-column -fsigned-zeros
 # -fsplit-ivs-in-unroller -fstdarg-opt -fstrict-volatile-bitfields
 # -fsync-libcalls -ftrapping-math -ftree-coalesce-vars -ftree-cselim
 # -ftree-forwprop -ftree-loop-if-convert -ftree-loop-im
 # -ftree-loop-ivcanon -ftree-loop-optimize -ftree-parallelize-loops=
 # -ftree-phiprop -ftree-reassoc -ftree-scev-cprop -funit-at-a-time
 # -funwind-tables -fverbose-asm -fzero-initialized-in-bss -m32 -m80387
 # -m96bit-long-double -maccumulate-outgoing-args -malign-double
 # -malign-stringops -mavx256-split-unaligned-load
 # -mavx256-split-unaligned-store -mfancy-math-387 -mfp-ret-in-387
 # -mieee-fp -mlong-double-80 -mms-bitfields -mno-red-zone -mno-sse4
 # -mpush-args -msahf -mstack-arg-probe -mvzeroupper

	.globl	_a
	.data
	.align 4
_a:
	.long	3
	.globl	_b
	.align 4
_b:
	.long	5
	.comm	_add, 4, 2
	.comm	_sub, 4, 2
	.comm	_mul, 4, 2
	.comm	_div, 4, 2
	.comm	_band, 4, 2
	.comm	_bor, 4, 2
	.comm	_bxor, 4, 2
	.comm	_bnot, 4, 2
	.comm	_land, 4, 2
	.comm	_lor, 4, 2
	.comm	_lnot, 4, 2
	.comm	_eq, 4, 2
	.comm	_neq, 4, 2
	.comm	_gt, 4, 2
	.comm	_lt, 4, 2
	.comm	_ge, 4, 2
	.comm	_le, 4, 2
	.text
	.globl	_op
	.def	_op;	.scl	2;	.type	32;	.endef
_op:
	pushl	%ebp	 #
	movl	%esp, %ebp	 #,
	movl	_a, %edx	 # a, D.1567
	movl	_b, %eax	 # b, D.1567
	addl	%edx, %eax	 # D.1567, D.1567
	movl	%eax, _add	 # D.1567, add
	movl	_a, %edx	 # a, D.1567
	movl	_b, %eax	 # b, D.1567
	subl	%eax, %edx	 # D.1567, D.1567
	movl	%edx, %eax	 # D.1567, D.1567
	movl	%eax, _sub	 # D.1567, sub
	movl	_a, %edx	 # a, D.1567
	movl	_b, %eax	 # b, D.1567
	imull	%edx, %eax	 # D.1567, D.1567
	movl	%eax, _mul	 # D.1567, mul
	movl	_a, %eax	 # a, D.1567
	movl	_b, %ecx	 # b, D.1567
	cltd
	idivl	%ecx	 # D.1567
	movl	%eax, _div	 # D.1567, div
	movl	_a, %edx	 # a, D.1567
	movl	_b, %eax	 # b, D.1567
	andl	%edx, %eax	 # D.1567, D.1567
	movl	%eax, _band	 # D.1567, band
	movl	_a, %edx	 # a, D.1567
	movl	_b, %eax	 # b, D.1567
	orl	%edx, %eax	 # D.1567, D.1567
	movl	%eax, _bor	 # D.1567, bor
	movl	_a, %edx	 # a, D.1567
	movl	_b, %eax	 # b, D.1567
	xorl	%edx, %eax	 # D.1567, D.1567
	movl	%eax, _bxor	 # D.1567, bxor
	movl	_a, %eax	 # a, D.1567
	notl	%eax	 # D.1567
	movl	%eax, _bnot	 # D.1567, bnot
	movl	_a, %eax	 # a, D.1567
	testl	%eax, %eax	 # D.1567
	je	L2	 #,
	movl	_b, %eax	 # b, D.1567
	testl	%eax, %eax	 # D.1567
	je	L2	 #,
	movl	$1, %eax	 #, D.1567
	jmp	L3	 #
L2:
	movl	$0, %eax	 #, D.1567
L3:
	movl	%eax, _land	 # D.1567, land
	movl	_a, %eax	 # a, D.1567
	testl	%eax, %eax	 # D.1567
	jne	L4	 #,
	movl	_b, %eax	 # b, D.1567
	testl	%eax, %eax	 # D.1567
	je	L5	 #,
L4:
	movl	$1, %eax	 #, D.1567
	jmp	L6	 #
L5:
	movl	$0, %eax	 #, D.1567
L6:
	movl	%eax, _lor	 # D.1567, lor
	movl	_a, %eax	 # a, D.1567
	testl	%eax, %eax	 # D.1567
	sete	%al	 #, D.1568
	movzbl	%al, %eax	 # D.1568, D.1567
	movl	%eax, _lnot	 # D.1567, lnot
	movl	_a, %edx	 # a, D.1567
	movl	_b, %eax	 # b, D.1567
	cmpl	%eax, %edx	 # D.1567, D.1567
	sete	%al	 #, D.1568
	movzbl	%al, %eax	 # D.1568, D.1567
	movl	%eax, _eq	 # D.1567, eq
	movl	_a, %edx	 # a, D.1567
	movl	_b, %eax	 # b, D.1567
	cmpl	%eax, %edx	 # D.1567, D.1567
	setne	%al	 #, D.1568
	movzbl	%al, %eax	 # D.1568, D.1567
	movl	%eax, _neq	 # D.1567, neq
	movl	_a, %edx	 # a, D.1567
	movl	_b, %eax	 # b, D.1567
	cmpl	%eax, %edx	 # D.1567, D.1567
	setg	%al	 #, D.1568
	movzbl	%al, %eax	 # D.1568, D.1567
	movl	%eax, _gt	 # D.1567, gt
	movl	_a, %edx	 # a, D.1567
	movl	_b, %eax	 # b, D.1567
	cmpl	%eax, %edx	 # D.1567, D.1567
	setl	%al	 #, D.1568
	movzbl	%al, %eax	 # D.1568, D.1567
	movl	%eax, _lt	 # D.1567, lt
	movl	_a, %edx	 # a, D.1567
	movl	_b, %eax	 # b, D.1567
	cmpl	%eax, %edx	 # D.1567, D.1567
	setge	%al	 #, D.1568
	movzbl	%al, %eax	 # D.1568, D.1567
	movl	%eax, _ge	 # D.1567, ge
	movl	_a, %edx	 # a, D.1567
	movl	_b, %eax	 # b, D.1567
	cmpl	%eax, %edx	 # D.1567, D.1567
	setle	%al	 #, D.1568
	movzbl	%al, %eax	 # D.1568, D.1567
	movl	%eax, _le	 # D.1567, le
	nop
	popl	%ebp	 #
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
