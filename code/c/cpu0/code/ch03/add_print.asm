.386
.model	flat
INCLUDELIB LIBCMT
printf PROTO C, format:PTR BYTE, args:VARARG
.data
num DWORD 0
formatStr BYTE "num=%d", 0dh, 0ah, 0
PUBLIC	_main
.code
_main	PROC
	MOV eax, 1
	ADD eax, 4
	SUB eax, 2
	MOV num, eax
	INVOKE printf, ADDR formatStr, num
	ret	0
_main	ENDP
END