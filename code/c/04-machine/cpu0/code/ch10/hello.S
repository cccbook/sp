.data
msg:	.ascii	"Hello World!\n"
		len = .-msg
.text
		.global	_start
_start:
#sys_write
		movl	$len, %edx
		movl	$msg, %ecx
		movl	$1, %ebx
		movl	$4,	%eax
		int		$0x80
#sys_exit
		movl	$0, %ebx
		movl	$1, %eax
		int		$0x80
		