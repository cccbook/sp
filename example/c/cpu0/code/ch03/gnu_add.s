	.text
.globl _asmMain
	.def _asmMain; .scl	2; .type 32; .endef
_asmMain:
	movl $1, %eax
	addl $4, %eax
	subl $2, %eax
	ret
