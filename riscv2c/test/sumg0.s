
#  extern printf  

#  file "sumg.c"  
	.file "sumg.c"
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

#  global s int 
	.comm	_s, 4, 2

#  global n int 
	.comm	_n, 4, 2

#  global i int 
	.comm	_i, 4, 2

#  str _Str2 "s=%d\n" 
	.section .rdata,"dr"
_Str2:
	.ascii "s=%d\n\0"
	.text

#  function sum int 
	.text
	.globl	_sum
	.def	sum;	.scl	2;	.type	32;	.endef
_sum:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp

#  = s 0 
	movl	$0, %ebx
	movl	%ebx, _s

#  = i 1 
	movl	$1, %ebx
	movl	%ebx, _i

#  label _WBEGIN0  
_WBEGIN0:

#  local t0  

#  <= t0 i n
	movl _i, %eax
	movl _n, %ebx
	cmpl %ebx, %eax
	setle %al
	movsbl	%al, %eax
	movl	%eax, -4(%ebp)

#  jz _WEND1 t0 
	movl	-4(%ebp), %eax
	cmpl	$0, %eax
	je	_WEND1

#  + t0 s i
	movl	_s, %eax
	addl	_i, %eax
	movl %eax, -4(%ebp)

#  = s t0 
	movl	-4(%ebp), %ebx
	movl	%ebx, _s

#  + t0 i 1
	movl	_i, %eax
	addl	$1, %eax
	movl %eax, -4(%ebp)

#  = i t0 
	movl	-4(%ebp), %ebx
	movl	%ebx, _i

#  jmp _WBEGIN0  
	jmp	_WBEGIN0

#  label _WEND1  
_WEND1:

#  return s  
	movl _s, %eax
	leave
	ret

#  -function sum  
	movl $0, %eax
	leave
	ret

#  function main int 
	.text
	.globl	_main
	.def	main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	call	___main

#  = n 10 
	movl	$10, %ebx
	movl	%ebx, _n

#  local t0  

#  call t0 sum 
	call ?sum
	movl %eax, -4(%ebp)

#  = s t0 
	movl	-4(%ebp), %ebx
	movl	%ebx, _s

#  arg _Str2  
	movl $_Str2, %eax
	movl %eax, 0(%esp)

#  arg s  
	movl _s, %eax
	movl %eax, 4(%esp)

#  call t0 printf 
	call _printf
	movl %eax, -4(%ebp)

#  -function main  
	movl $0, %eax
	leave
	ret

#  -file "sumg.c"  
	.ident	"c0c: 0.0.1"
	.def	_puts;	.scl	2;	.type	32;	.endef
