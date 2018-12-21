.386
.model	flat
INCLUDELIB LIBCMT
printf PROTO C, format:PTR BYTE, args:VARARG
.data
sum DWORD 0
formatStr BYTE "sum=%d", 0dh, 0ah, 0
PUBLIC	_main
.code
_main	PROC
	MOV eax, 1
FOR1:
	ADD sum, eax
	ADD eax, 1
	CMP eax, 10
	JLE FOR1
	INVOKE printf, ADDR formatStr, sum
	ret	0
_main	ENDP
END
