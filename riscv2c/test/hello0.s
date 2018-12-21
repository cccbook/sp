# file "hello.c"  
	.file "hello.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.comm	_t0, 4, 2
	.comm	_t1, 4, 2
	.comm	_t2, 4, 2
	.comm	_t3, 4, 2
	.comm	_t4, 4, 2
	.comm	_t5, 4, 2
	.comm	_t6, 4, 2
	.comm	_t7, 4, 2
	.comm	_t8, 4, 2
# function _main _int 
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	call	___main
# str _S0 "Hello!\n" 
	.section .rdata,"dr"
_S0:
	.ascii "Hello!\n"
	.text
# arg _S0 $0 
	movl $_S0, 0(%esp)
# call _t0 _printf $1
	call _printf
	movl %eax, _t0
# fend _main  
	leave
	ret
