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

sum.s

```
	.file	"sum.c"
	.text
	.globl	_sum
	.def	_sum;	.scl	2;	.type	32;	.endef
_sum:
	pushl	%ebp	 #
	movl	%esp, %ebp	 #,
	subl	$16, %esp	 #,
	movl	$0, -4(%ebp)	 #, s
	movl	$0, -8(%ebp)	 #, i
	jmp	L2	 #
L3:
	movl	-8(%ebp), %eax	 # i, tmp89
	addl	%eax, -4(%ebp)	 # tmp89, s
	addl	$1, -8(%ebp)	 #, i
L2:
	movl	-8(%ebp), %eax	 # i, tmp90
	cmpl	8(%ebp), %eax	 # n, tmp90
	jle	L3	 #,
	movl	-4(%ebp), %eax	 # s, D.1492
	leave
	ret
	.ident	"GCC: (tdm-1) 5.1.0"

```

## 將組合語言轉換為目的檔

```
$ gcc -c sum.s -o sum.o
```

## objdump 反組譯目的檔


傾印目的檔

```
$ objdump -s sum.o

sum.o:     file format pe-i386

Contents of section .text:
 0000 5589e583 ec10c745 fc000000 00c745f8  U......E......E.
 0010 00000000 eb0a8b45 f80145fc 8345f801  .......E..E..E..
 0020 8b45f83b 45087eee 8b45fcc9 c3909090  .E.;E.~..E......
Contents of section .rdata$zzz:
 0000 4743433a 20287464 6d2d3129 20352e31  GCC: (tdm-1) 5.1
 0010 2e300000                             .0..
```

反組譯目的檔

```
$ objdump -d sum.o

sum.o:     file format pe-i386


Disassembly of section .text:

00000000 <_sum>:
   0:   55                      push   %ebp
   1:   89 e5                   mov    %esp,%ebp
   3:   83 ec 10                sub    $0x10,%esp
   6:   c7 45 fc 00 00 00 00    movl   $0x0,-0x4(%ebp)
   d:   c7 45 f8 00 00 00 00    movl   $0x0,-0x8(%ebp)
  14:   eb 0a                   jmp    20 <_sum+0x20>
  16:   8b 45 f8                mov    -0x8(%ebp),%eax
  19:   01 45 fc                add    %eax,-0x4(%ebp)
  1c:   83 45 f8 01             addl   $0x1,-0x8(%ebp)
  20:   8b 45 f8                mov    -0x8(%ebp),%eax
  23:   3b 45 08                cmp    0x8(%ebp),%eax
  26:   7e ee                   jle    16 <_sum+0x16>
  28:   8b 45 fc                mov    -0x4(%ebp),%eax
  2b:   c9                      leave
  2c:   c3                      ret
  2d:   90                      nop
  2e:   90                      nop
  2f:   90                      nop
```