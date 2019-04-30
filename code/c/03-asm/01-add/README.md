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
$ gcc -fverbose-asm -S add.c -o add.s
$ gcc main.s add.s -o add
$ ./add
add(5, 8)=13
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

## 解說

add.s

```
	.file	"add.c"             // 原始碼是 add.c
	.text                     // 程式段開始
	.globl	_add              // _add 是個全域 Global 標記
	.def	_add;	.scl	2;	.type	32;	.endef // 32 位元，參考 https://stackoverflow.com/questions/1317081/gccs-assembly-output-of-an-empty-program-on-x86-win32
_add:                       // _add 標記
	pushl	%ebp	 #            // 將 ebp 框架暫存器推入堆疊
	movl	%esp, %ebp	 #,     // ebp = esp, 新的框架位址 
	movl	8(%ebp), %edx	 # a, tmp89 // 將 a 放入 edx
	movl	12(%ebp), %eax	 # b, tmp90 // 將 b 放入 eax
	addl	%edx, %eax	 # tmp89, D.1488 // eax = a+b
	popl	%ebp	 #            // 恢復呼叫前的 ebp
	ret                       // 返回上一層
	.ident	"GCC: (tdm-1) 5.1.0"
```

* https://eli.thegreenplace.net/2011/02/04/where-the-top-of-the-stack-is-on-x86

繪圖說明 call/ret 的原理

* https://segmentfault.com/q/1010000007057142

```
leave
ret
```

相當於

```
movl    %ebp, %esp
popl    %ebp
popl    %eip
```

* https://stackoverflow.com/questions/20129107/what-is-the-x86-ret-instruction-equivalent-to


## 主程式解說

```
	.file	"main.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "add(5, 8)=%d\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp	 #
	movl	%esp, %ebp	 #,
	andl	$-16, %esp	 #,
	subl	$32, %esp	 #,               // 框架大小分配 32
	call	___main	 #
	movl	$8, 4(%esp)	 #,             // 準備參數 b=8
	movl	$5, (%esp)	 #,             //         a=5
	call	_add	 #                    // 呼叫 add(a,b)
	movl	%eax, 28(%esp)	 # tmp89, t // t = eax
	movl	28(%esp), %eax	 # t, tmp90
	movl	%eax, 4(%esp)	 # tmp90,     // 將 t 放到堆疊
	movl	$LC0, (%esp)	 #,           // 將 LC0 放入堆疊
	call	_printf	 #                  // 呼叫 _printf
	movl	$0, %eax	 #, D.1933        // 設定傳回值 eax 為 0
	leave                             // 準備離開，恢復框架
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
	.def	_add;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
```

說明: https://stackoverflow.com/questions/7060970/substitutes-for-x86-assembly-call-instruction

影片: 

1. x86 Assembly #9 - Calling Conventions | cdecl
    * https://www.youtube.com/watch?v=frqPX7EHscM&list=PLan2CeTAw3pFOq5qc9urw8w7R-kvAT8Yb&index=9
2. x86 Assembly #10 - CALL | Call Instruction (讚!)
    * https://www.youtube.com/watch?v=xAK1pGf_QHw
3. x86 Assembly #11 - RET | Return Instruction (讚!)
    * https://www.youtube.com/watch?v=32zR57OTrAQ&list=PLan2CeTAw3pFOq5qc9urw8w7R-kvAT8Yb&index=11
4. x86 Assembly #27 - Local Variables and Arguments Passing | Part 2
    * https://www.youtube.com/watch?v=C8qASvZGHSo&list=PLan2CeTAw3pFOq5qc9urw8w7R-kvAT8Yb&index=27

## 使用 gdb


參考 : https://linuxtools-rst.readthedocs.io/zh_CN/latest/tool/gdb.html

在 MSYS2 中 ...

```
user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c/03-asm/01-add
$ gcc main.c add.c -o add -g

user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c/03-asm/01-add
$ gdb -q add
Traceback (most recent call last):
  File "<string>", line 3, in <module>
ImportError: No module named libstdcxx.v6.printers
/etc/gdbinit:6: Error in sourced command file:
Error while executing Python code.
Reading symbols from add...done.
(gdb) break 6
Breakpoint 1 at 0x10040108d: file main.c, line 6.
(gdb) r
Starting program: /d/ccc/book/sp/code/c/03-asm/01-add/add
[New Thread 1896.0x26cc]
[New Thread 1896.0x13b8]
[New Thread 1896.0xb84]
[New Thread 1896.0x22ec]

Thread 1 "add" hit Breakpoint 1, main () at main.c:6
6         int t = add(5, 8);
(gdb) n
7         printf("add(5, 8)=%d\n", t);
(gdb) n
add(5, 8)=13
8       }(gdb) n
[Thread 1896.0x22ec exited with code 0]
[Thread 1896.0x13b8 exited with code 0]
[Inferior 1 (process 1896) exited normally]
(gdb)

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