	.file	"sum.c"
	.option nopic
# GNU C99 (GCC) version 8.2.0 (riscv64-unknown-elf)
#	compiled by GNU C version 4.2.1 Compatible Apple LLVM 10.0.0 (clang-1000.10.44.4), GMP version 6.1.2, MPFR version 4.0.1, MPC version 1.1.0, isl version isl-0.20-GMP

# GGC heuristics: --param ggc-min-expand=30 --param ggc-min-heapsize=4096
# options passed:  sum.c -march=rv64imafdc -mabi=lp64d -auxbase-strip sum.s
# -O0 -std=c99 -fverbose-asm
# options enabled:  -faggressive-loop-optimizations -fauto-inc-dec
# -fchkp-check-incomplete-type -fchkp-check-read -fchkp-check-write
# -fchkp-instrument-calls -fchkp-narrow-bounds -fchkp-optimize
# -fchkp-store-bounds -fchkp-use-static-bounds
# -fchkp-use-static-const-bounds -fchkp-use-wrappers -fcommon
# -fdelete-null-pointer-checks -fdwarf2-cfi-asm -fearly-inlining
# -feliminate-unused-debug-types -ffp-int-builtin-inexact -ffunction-cse
# -fgcse-lm -fgnu-runtime -fgnu-unique -fident -finline-atomics
# -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
# -fivopts -fkeep-static-consts -fleading-underscore -flifetime-dse
# -flto-odr-type-merging -fmath-errno -fmerge-debug-strings -fpeephole
# -fplt -fprefetch-loop-arrays -freg-struct-return
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
# -fshow-column -fshrink-wrap-separate -fsigned-zeros
# -fsplit-ivs-in-unroller -fssa-backprop -fstdarg-opt
# -fstrict-volatile-bitfields -fsync-libcalls -ftrapping-math
# -ftree-forwprop -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
# -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop
# -ftree-reassoc -ftree-scev-cprop -funit-at-a-time -fverbose-asm
# -fzero-initialized-in-bss -mdiv -mexplicit-relocs -mfdiv -mplt
# -mstrict-align

	.text
	.align	1
	.globl	sum
	.type	sum, @function
sum:
	addi	sp,sp,-48	#,,
	sd	s0,40(sp)	#,
	addi	s0,sp,48	#,,
	mv	a5,a0	# tmp74, n
	sw	a5,-36(s0)	# tmp75, n
# sum.c:5:   for (int i=0; i<=n; i++) {
	sw	zero,-24(s0)	#, i
# sum.c:5:   for (int i=0; i<=n; i++) {
	j	.L2		#
.L3:
# sum.c:6:     s=s+i;
	lw	a4,-20(s0)		# tmp77, s
	lw	a5,-24(s0)		# tmp78, i
	addw	a5,a4,a5	# tmp78, tmp76, tmp77
	sw	a5,-20(s0)	# tmp76, s
# sum.c:5:   for (int i=0; i<=n; i++) {
	lw	a5,-24(s0)		# tmp80, i
	addiw	a5,a5,1	#, tmp79, tmp80
	sw	a5,-24(s0)	# tmp79, i
.L2:
# sum.c:5:   for (int i=0; i<=n; i++) {
	lw	a4,-24(s0)		# tmp81, i
	lw	a5,-36(s0)		# tmp82, n
	sext.w	a4,a4	# tmp83, tmp81
	sext.w	a5,a5	# tmp84, tmp82
	ble	a4,a5,.L3	#, tmp83, tmp84,
# sum.c:8:   return s;
	lw	a5,-20(s0)		# _8, s
# sum.c:9: }
	mv	a0,a5	#, <retval>
	ld	s0,40(sp)		#,
	addi	sp,sp,48	#,,
	jr	ra		#
	.size	sum, .-sum
	.ident	"GCC: (GNU) 8.2.0"
