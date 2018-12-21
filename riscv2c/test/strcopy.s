	.file	"strcopy.c"
 # GNU C11 (tdm-1) version 5.1.0 (mingw32)
 #	compiled by GNU C version 5.1.0, GMP version 4.3.2, MPFR version 2.4.2, MPC version 0.8.2
 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: 
 # -iprefix C:/Program Files (x86)/CodeBlocks/MinGW/bin/../lib/gcc/mingw32/5.1.0/
 # -D_REENTRANT strcopy.c -mtune=generic -march=pentiumpro
 # -auxbase-strip strcopy.s -fverbose-asm
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

	.text
	.globl	_strcopy
	.def	_strcopy;	.scl	2;	.type	32;	.endef
_strcopy:
	pushl	%ebp	 #
	movl	%esp, %ebp	 #,
	subl	$96, %esp	 #,
	movl	$0, -4(%ebp)	 #, i
	movb	$32, -5(%ebp)	 #, c
	movb	$0, -6(%ebp)	 #, end
	movl	$1, -12(%ebp)	 #, x
	movl	$2, -16(%ebp)	 #, y
	movl	$3, -20(%ebp)	 #, z
	movl	$4, -24(%ebp)	 #, w
	movl	$5, -28(%ebp)	 #, k
	movl	$6, -32(%ebp)	 #, l
	movl	$7, -36(%ebp)	 #, m
	jmp	L2	 #
L4:
	movl	8(%ebp), %eax	 # t, tmp91
	movzbl	(%eax), %eax	 # *t_1, tmp92
	movb	%al, -5(%ebp)	 # tmp92, c
	movl	12(%ebp), %eax	 # s, tmp93
	movzbl	-5(%ebp), %edx	 # c, tmp94
	movb	%dl, (%eax)	 # tmp94, *s_2
	addl	$1, 12(%ebp)	 #, s
	addl	$1, 8(%ebp)	 #, t
	addl	$1, -4(%ebp)	 #, i
L2:
	movl	-4(%ebp), %eax	 # i, tmp95
	cmpl	16(%ebp), %eax	 # len, tmp95
	jge	L3	 #,
	movl	12(%ebp), %eax	 # s, tmp96
	movzbl	(%eax), %eax	 # *s_2, D.1518
	cmpb	-6(%ebp), %al	 # end, D.1518
	jne	L4	 #,
L3:
	movl	12(%ebp), %eax	 # s, tmp97
	movzbl	-6(%ebp), %edx	 # end, tmp98
	movb	%dl, (%eax)	 # tmp98, *s_2
	movl	-4(%ebp), %eax	 # i, tmp99
	imull	20(%ebp), %eax	 # scale, D.1519
	imull	-12(%ebp), %eax	 # x, D.1519
	leave
	ret
	.globl	_c
	.section .rdata,"dr"
LC0:
	.ascii "global constant\0"
	.data
	.align 4
_c:
	.long	LC0
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC1:
	.ascii "hello! how are you ?\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp	 #
	movl	%esp, %ebp	 #,
	andl	$-16, %esp	 #,
	subl	$32, %esp	 #,
	call	___main	 #
	movl	$LC1, 28(%esp)	 #, a
	movl	$10, 24(%esp)	 #, len
	movl	$4, 20(%esp)	 #, scale
	movl	_c, %eax	 # c, D.1521
	movl	20(%esp), %edx	 # scale, tmp90
	movl	%edx, 12(%esp)	 # tmp90,
	movl	24(%esp), %edx	 # len, tmp91
	movl	%edx, 8(%esp)	 # tmp91,
	movl	%eax, 4(%esp)	 # D.1521,
	movl	28(%esp), %eax	 # a, tmp92
	movl	%eax, (%esp)	 # tmp92,
	call	_strcopy	 #
	movl	$0, %eax	 #, D.1522
	leave
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
