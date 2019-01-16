# 組合語言與機器碼

## 用 gcc 編譯 C 程式

```
$ gcc main.c sum.c -o sum
$ ./sum
sum(10)=55
```

## 用 gcc 產生組合語言

```
$ gcc -fverbose-asm -S main.c -o main.s
$ gcc -fverbose-asm -S sum.c -o sum.s
```

add.s

```
	.file	"add.c"
	.text
	.globl	_add
	.def	_add;	.scl	2;	.type	32;	.endef
_add:
	pushl	%ebp	 #
	movl	%esp, %ebp	 #,
	movl	8(%ebp), %edx	 # a, tmp89
	movl	12(%ebp), %eax	 # b, tmp90
	addl	%edx, %eax	 # tmp89, D.1488
	popl	%ebp	 #
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
```

## 將組合語言轉換為目的檔

```
$ gcc -c add.s -o add.o
```

## objdump 反組譯目的檔


傾印目的檔

```
$ objdump -s add.o

add.o:     file format pe-i386

Contents of section .text:
 0000 5589e58b 55088b45 0c01d05d c3909090  U...U..E...]....
Contents of section .rdata$zzz:
 0000 4743433a 20287464 6d2d3129 20352e31  GCC: (tdm-1) 5.1
 0010 2e300000                             .0..
```

反組譯目的檔

```
$ objdump -d add.o

add.o:     file format pe-i386


Disassembly of section .text:

00000000 <_add>:
   0:   55                      push   %ebp
   1:   89 e5                   mov    %esp,%ebp
   3:   8b 55 08                mov    0x8(%ebp),%edx
   6:   8b 45 0c                mov    0xc(%ebp),%eax
   9:   01 d0                   add    %edx,%eax
   b:   5d                      pop    %ebp
   c:   c3                      ret
   d:   90                      nop
   e:   90                      nop
   f:   90                      nop
```