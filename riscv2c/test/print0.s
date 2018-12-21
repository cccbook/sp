
#  extern printf  

#  file "print.c"  
	.file "print.c"
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

#  global n int 
	.comm	_n, 4, 2

#  str _Str2 "n>5\n" 
	.section .rdata,"dr"
_Str2:
	.ascii "n>5\n\0"
	.text

#  str _Str3 "n<=5\n" 
	.section .rdata,"dr"
_Str3:
	.ascii "n<=5\n\0"
	.text

#  str _Str4 "Hello %d!\n" 
	.section .rdata,"dr"
_Str4:
	.ascii "Hello %d!\n\0"
	.text

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

#  = n 7 
	movl	$7, %ebx
	movl	%ebx, _n

#  local t0  

#  > t0 n 5
	movl _n, %eax
	movl $5, %ebx
	cmpl %ebx, %eax
	setg %al
	movsbl	%al, %eax
	movl	%eax, -4(%ebp)

#  jz _ELSE0 t0 
	movl	-4(%ebp), %eax
	cmpl	$0, %eax
	je	_ELSE0

#  arg _Str2  
	movl $_Str2, %eax
	movl %eax, 0(%esp)

#  call t0 printf 
	call _printf
	movl %eax, -4(%ebp)

#  jmp _ENDIF1  
	jmp	_ENDIF1

#  label _ELSE0  
_ELSE0:

#  arg _Str3  
	movl $_Str3, %eax
	movl %eax, 0(%esp)

#  call t0 printf 
	call _printf
	movl %eax, -4(%ebp)

#  label _ENDIF1  
_ENDIF1:

#  arg _Str4  
	movl $_Str4, %eax
	movl %eax, 0(%esp)

#  arg n  
	movl _n, %eax
	movl %eax, 4(%esp)

#  call t0 printf 
	call _printf
	movl %eax, -4(%ebp)

#  return 8  
	movl $8, %eax
	leave
	ret

#  -function main  
	movl $0, %eax
	leave
	ret

#  -file "print.c"  
	.ident	"c0c: 0.0.1"
	.def	_puts;	.scl	2;	.type	32;	.endef
