# 用 gcc 解讀 x86 組合語言

## op.c

FILE op.c

```c
int op(int a, int b) {
  return (a*a*17 + b * a + 9 + b * b * 3);
}
```

組合語言 op.s

```
	.file	"op.c"
	.text
	.globl	_op
	.def	_op;	.scl	2;	.type	32;	.endef
_op:
	pushl	%ebp	 #
	movl	%esp, %ebp	 #,
	movl	8(%ebp), %edx	 # a, tmp93
	movl	%edx, %eax	 # tmp93, tmp94
	addl	%eax, %eax	 # tmp94
	addl	%eax, %edx	 # tmp94, D.1492
	movl	12(%ebp), %eax	 # b, tmp95
	sall	$2, %eax	 #, D.1492
	leal	(%edx,%eax), %ecx	 #, D.1492
	movl	$1717986919, %edx	 #, tmp97
	movl	%ecx, %eax	 # D.1492, tmp101
	imull	%edx	 # tmp97
	sarl	%edx	 # tmp98
	movl	%ecx, %eax	 # D.1492, tmp99
	sarl	$31, %eax	 #, tmp99
	subl	%eax, %edx	 # tmp99, D.1492
	movl	%edx, %eax	 # D.1492, D.1492
	addl	$1, %eax	 #, D.1492
	popl	%ebp	 #
	ret
	.ident	"GCC: (tdm-1) 5.1.0"

```

我的解讀

```c
int op(int a, int b) {
  return (a*a*17 + b * a + 9 + b * b * 3);
}
```

```
	.text
	.globl	_op
	.def	_op;	.scl	2;	.type	32;	.endef
_op:
	pushl	%ebp	 #
	movl	%esp, %ebp	 #,
	movl	8(%ebp), %eax	 # a, tmp96       eax = a
	imull	8(%ebp), %eax	 # a, D.1495      eax = eax * a
	movl	%eax, %edx	 # D.1495, D.1495   edx = eax = a*a
	movl	%edx, %eax	 # D.1495, tmp97    eax = edx = a*a
	sall	$4, %eax	 #, tmp98             eax = eax * 16
	addl	%eax, %edx	 # tmp97, D.1495    edx = eax + a = 17 * a * a
	movl	12(%ebp), %eax	 # b, tmp99     eax = b
	imull	8(%ebp), %eax	 # a, D.1495      eax = a * b
	addl	%edx, %eax	 # D.1495, D.1495   eax = edx + eax = 17*a*a + a*b
	leal	9(%eax), %ecx	 #, D.1495        ecx = eax + 9 =  17*a*a + a*b + 9
	movl	12(%ebp), %eax	 # b, tmp100    eax = b
	imull	12(%ebp), %eax	 # b, D.1495    eax = b*b
	movl	%eax, %edx	 # D.1495, D.1495   edx = b*b
	movl	%edx, %eax	 # D.1495, tmp101   eax = b*b
	addl	%eax, %eax	 # tmp101           eax = b*b*2
	addl	%edx, %eax	 # D.1495, D.1495   eax = b*b*3
	addl	%ecx, %eax	 # D.1495, D.1495   eax = eax + ecx =  17*a*a + a*b + 9 + b*b*3
	popl	%ebp	 #
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
```

## asum.c

原始程式

FILE: asum.c

```c
int total(int *a, int size) {
  int s, i;
  s = 0;
  i = 0;
  while (i < size) {
    s = s + a[i];
  }
  return s;
}
```

產生組合語言

```
$ gcc -S -fverbose-asm asum.c -o asum.s
```

FILE: asum.s

```
	.file	"asum.c"
	.text
	.globl	_total
	.def	_total;	.scl	2;	.type	32;	.endef
_total:
	pushl	%ebp	 #
	movl	%esp, %ebp	 #,
	subl	$16, %esp	 #,
	movl	$0, -4(%ebp)	 #, s
	movl	$0, -8(%ebp)	 #, i
	jmp	L2	 #
L3:
	movl	-8(%ebp), %eax	 # i, D.1497
	leal	0(,%eax,4), %edx	 #, D.1497
	movl	8(%ebp), %eax	 # a, tmp93
	addl	%edx, %eax	 # D.1497, D.1498
	movl	(%eax), %eax	 # *_8, D.1499
	addl	%eax, -4(%ebp)	 # D.1499, s
L2:
	movl	-8(%ebp), %eax	 # i, tmp94
	cmpl	12(%ebp), %eax	 # size, tmp94
	jl	L3	 #,
	movl	-4(%ebp), %eax	 # s, D.1499
	leave
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
```

加上我的註解

```
	.file	"asum.c"
	.text
	.globl	_total
	.def	_total;	.scl	2;	.type	32;	.endef
_total:                  #                 int total(int *a, int size)
                         #                 框架變數 size: 12(%ebp), a: 8(%ebp) 返回位址?: 4(%ebp) 保留 ebp?: 0(%ebp)
                         #                 int s, i;  s: -4(%ebp), i:-8(%ebp)
	pushl	%ebp	           # 保存 ebp
	movl	%esp, %ebp	     # ebp = esp 是 pushl %ebp 完了之後的事，所以上一個 ebp 已經在堆疊頂端了。
	subl	$16, %esp	       # esp = esp - 16  似乎是為了效能或對齊的原因，這邊的框架分配量一定要是 16 的倍數！
	movl	$0, -4(%ebp)     # s               s = 0
	movl	$0, -8(%ebp)	   # i               i = 0
	jmp	L2	 #
L3:                      #                 s = s + a[i]
	movl	-8(%ebp), %eax	 # i, D.1497       eax = i 
                         # 參考: https://sourceware.org/binutils/docs-2.18/as/i386_002dMemory.html
                         #      target = disp(base,%eax,4) = [base + index*scale + disp]
	leal	0(,%eax,4), %edx #, D.1497         edx = eax * 4  // 因為 a 陣列型態為 int，所以索引位址都要乘上 4
	movl	8(%ebp), %eax	   # a, tmp93        eax = a
	addl	%edx, %eax	     # D.1497, D.1498  eax = a+i
	movl	(%eax), %eax	   # *_8, D.1499     eax = *(a+i)
	addl	%eax, -4(%ebp)	 # D.1499, s       s = eax
L2:
	movl	-8(%ebp), %eax	 # i, tmp94        i < size
	cmpl	12(%ebp), %eax	 # size, tmp94
	jl	L3	               #
	movl	-4(%ebp), %eax	 # s, D.1499       return s
	leave
	ret
	.ident	"GCC: (tdm-1) 5.1.0"

```

## strcopy.c

```c
int strcopy(char *t, char *s, int len, int scale) {
  int  i = 0;
  // char temp[100];
  char c = ' ';
  char end = '\0';
  while (i < len && *s != end) {
    c = *t;
    *s = c;
    s++;
    t++;
    i++;
    // temp[i] = *t;
  }
  *s = end;
  return i * scale;
}

int main() {
  char *a = "hello! how are you ?", *b="world! just xxx";
  int len=10, scale=4;
  strcopy(a, b, len, scale);
}

```

FILE strcopy.s

```
	.file	"strcopy.c"
	.text
	.globl	_strcopy
	.def	_strcopy;	.scl	2;	.type	32;	.endef
_strcopy:
	pushl	%ebp	 #
	movl	%esp, %ebp	 #,
	subl	$16, %esp	 #,
	movl	$0, -4(%ebp)	 #, i
	movb	$32, -5(%ebp)	 #, c
	movb	$0, -6(%ebp)	 #, end
	jmp	L2	 #
L4:
	movl	8(%ebp), %eax	 # t, tmp90
	movzbl	(%eax), %eax	 # *t_1, tmp91
	movb	%al, -5(%ebp)	 # tmp91, c
	movl	12(%ebp), %eax	 # s, tmp92
	movzbl	-5(%ebp), %edx	 # c, tmp93
	movb	%dl, (%eax)	 # tmp93, *s_2
	addl	$1, 12(%ebp)	 #, s
	addl	$1, 8(%ebp)	 #, t
	addl	$1, -4(%ebp)	 #, i
L2:
	movl	-4(%ebp), %eax	 # i, tmp94
	cmpl	16(%ebp), %eax	 # len, tmp94
	jge	L3	 #,
	movl	12(%ebp), %eax	 # s, tmp95
	movzbl	(%eax), %eax	 # *s_2, D.1507
	cmpb	-6(%ebp), %al	 # end, D.1507
	jne	L4	 #,
L3:
	movl	12(%ebp), %eax	 # s, tmp96
	movzbl	-6(%ebp), %edx	 # end, tmp97
	movb	%dl, (%eax)	 # tmp97, *s_2
	movl	-4(%ebp), %eax	 # i, tmp98
	imull	20(%ebp), %eax	 # scale, D.1508
	leave
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "hello! how are you ?\0"
LC1:
	.ascii "world! just xxx\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp	 #
	movl	%esp, %ebp	 #,
	andl	$-16, %esp	 #,
	subl	$32, %esp	 #,
	call	___main	 #
	movl	$LC0, 28(%esp)	 #, a
	movl	$LC1, 24(%esp)	 #, b
	movl	$10, 20(%esp)	 #, len
	movl	$4, 16(%esp)	 #, scale
	movl	16(%esp), %eax	 # scale, tmp89
	movl	%eax, 12(%esp)	 # tmp89,
	movl	20(%esp), %eax	 # len, tmp90
	movl	%eax, 8(%esp)	 # tmp90,
	movl	24(%esp), %eax	 # b, tmp91
	movl	%eax, 4(%esp)	 # tmp91,
	movl	28(%esp), %eax	 # a, tmp92
	movl	%eax, (%esp)	 # tmp92,
	call	_strcopy	 #
	movl	$0, %eax	 #, D.1509
	leave
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
```

加上我的註解：

```
	.file	"strcopy.c"
	.text
	.globl	_strcopy
	.def	_strcopy;	.scl	2;	.type	32;	.endef
_strcopy:
	pushl	%ebp	 #
	movl	%esp, %ebp	 #,
	subl	$16, %esp	                # 似乎是為了效能的原因，這邊的框架分配量一定要是 16 的倍數！
	movl	$0, -4(%ebp)	 #, i
	movb	$32, -5(%ebp)	 #, c
	movb	$0, -6(%ebp)	 #, end
	jmp	L2	 #
L4:
	movl	8(%ebp), %eax	 # t, tmp90
	movzbl	(%eax), %eax	 # *t_1, tmp91
	movb	%al, -5(%ebp)	 # tmp91, c
	movl	12(%ebp), %eax	 # s, tmp92
	movzbl	-5(%ebp), %edx	 # c, tmp93
	movb	%dl, (%eax)	 # tmp93, *s_2
	addl	$1, 12(%ebp)	 #, s
	addl	$1, 8(%ebp)	 #, t
	addl	$1, -4(%ebp)	 #, i
L2:
	movl	-4(%ebp), %eax	 # i, tmp94
	cmpl	16(%ebp), %eax	 # len, tmp94
	jge	L3	 #,
	movl	12(%ebp), %eax	 # s, tmp95
	movzbl	(%eax), %eax	 # *s_2, D.1507
	cmpb	-6(%ebp), %al	 # end, D.1507
	jne	L4	 #,
L3:
	movl	12(%ebp), %eax	 # s, tmp96
	movzbl	-6(%ebp), %edx	 # end, tmp97
	movb	%dl, (%eax)	 # tmp97, *s_2
	movl	-4(%ebp), %eax	 # i, tmp98
	imull	20(%ebp), %eax	 # scale, D.1508
	leave
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "hello! how are you ?\0"
LC1:
	.ascii "world! just xxx\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp	 #
	movl	%esp, %ebp	 #,
	andl	$-16, %esp	 #,
	subl	$32, %esp	       #, a, b, len, scale + _strcopy 呼叫時的四個參數！ (幒共 4*8 = 32)
	call	___main	 #
	movl	$LC0, 28(%esp)	 #, a
	movl	$LC1, 24(%esp)	 #, b
	movl	$10, 20(%esp)	 #, len
	movl	$4, 16(%esp)	 #, scale
	movl	16(%esp), %eax	 # scale, tmp89
	movl	%eax, 12(%esp)	 # tmp89,        有繼續往下呼叫 _strcopy, 就得推入參數到堆疊中傳入。
	movl	20(%esp), %eax	 # len, tmp90
	movl	%eax, 8(%esp)	 # tmp90,
	movl	24(%esp), %eax	 # b, tmp91
	movl	%eax, 4(%esp)	 # tmp91,
	movl	28(%esp), %eax	 # a, tmp92
	movl	%eax, (%esp)	 # tmp92,
	call	_strcopy	 #
	movl	$0, %eax	 #, D.1509
	leave
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
```
