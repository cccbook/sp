# file "gfunc.c"  
.file "gfunc.c"
# global _s _int 
	.comm	_s, 4, 2
# global _i _int 
	.comm	_i, 4, 2
# global _n _int 
	.comm	_n, 4, 2
  .comm	_t0, 4, 2
  .comm	_t1, 4, 2
# function _sum _int 
	.text
	.globl	_sum
	.def	_sum;	.scl	2;	.type	32;	.endef
_sum:
	pushl	%ebp
	movl	%esp, %ebp
# = _s $0 
	movl	$0, %ebx
	movl	%ebx, _s
# = _i $1 
	movl	$1, %ebx
	movl	%ebx, _i
_WBEGIN0:
# <= _t0 _i _n
	movl _i, %eax
	movl _n, %ebx
	cmpl %eax, %ebx
	setle %al
	movzbl	%al, %eax
	movl	%eax, _t0
# jnz _WEND1 _t0 
	movl	_t0, %eax
	cmpl	%eax, 0
	jne	_WEND1
# + _t0 _s _i
	movl	_s, %eax
	addl	_i, %eax
	movl %eax, _t0
# = _s _t0 
	movl	_t0, %ebx
	movl	%ebx, _s
# ++ _i  
# + _i _i $1
	movl	_i, %eax
	addl	$1, %eax
	movl %eax, _i
# jmp _WBEGIN0  
	jmp	_WBEGIN0
_WEND1:
# return _s  
	movl _s, %eax
	ret
# fend _sum  
	leave
	ret
# function _main _int 
# str _S2 "sum(%d)=%d\n" 
	.section .rdata,"dr"
_S2:
	.ascii "sum(%d)=%d\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	call	___main
# = _n $10 
	movl	$10, %ebx
	movl	%ebx, _n
# push _S2  
	#push	_S2
# push _n  
	#push	_n
# call _t0 _sum 
	call _sum
	movl %eax, _t0
# push _t0  
	#push	_t0
# call _t1 _printf
  movl  _sum, %ebx
	movl	%ebx, 8(%esp)
  movl  _n, %ebx
	movl	%ebx, 4(%esp)
	movl	$_S2, (%esp)
	call _printf
	movl %eax, _t1
# fend _main  
	leave
	ret
