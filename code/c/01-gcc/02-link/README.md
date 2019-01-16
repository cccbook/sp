# ld -- Gcc Linker

## 直接編譯連結

```
$ gcc main.c sum.c -o run.o
$ ./run.o
```

## 產生組合語言

```
$ gcc -S main.c -o main.s
$ gcc -S sum.c -o sum.s
```

## 組譯後連結

```
$ gcc main.c sum.s -o run.o
$ ./run.o
sum(10)=55
```

## 產生目的檔

```
$ gcc -c sum.c -o sum.o
$ gcc -c main.c -o main.o
```

## 連結目的檔

```
$ gcc main.o sum.o -o run.o
$ ./run.o
```

## 反組譯

```
$ objdump -d sum.o


sum.o:  file format Mach-O 64-bit x86-64

Disassembly of section __TEXT,__text:
_sum:
       0:       55      pushq   %rbp
       1:       48 89 e5        movq    %rsp, %rbp
       4:       89 7d fc        movl    %edi, -4(%rbp)
       7:       c7 45 f8 00 00 00 00    movl    $0, -8(%rbp)
       e:       c7 45 f4 00 00 00 00    movl    $0, -12(%rbp)
      15:       8b 45 f4        movl    -12(%rbp), %eax
      18:       3b 45 fc        cmpl    -4(%rbp), %eax
      1b:       0f 8f 17 00 00 00       jg      23 <_sum+0x38>
      21:       8b 45 f8        movl    -8(%rbp), %eax
      24:       03 45 f4        addl    -12(%rbp), %eax
      27:       89 45 f8        movl    %eax, -8(%rbp)
      2a:       8b 45 f4        movl    -12(%rbp), %eax
      2d:       83 c0 01        addl    $1, %eax
      30:       89 45 f4        movl    %eax, -12(%rbp)
      33:       e9 dd ff ff ff  jmp     -35 <_sum+0x15>
      38:       8b 45 f8        movl    -8(%rbp), %eax
      3b:       5d      popq    %rbp
      3c:       c3      retq
```

## sum.s 組合語言解讀版

```
  .section	__TEXT,__text,regular,pure_instructions
  .macosx_version_min 10, 13
  .globl	_sum
  .p2align	4, 0x90
_sum:                                   ## @sum
  .cfi_startproc
## BB#0:
  pushq	%rbp          ## 儲存上一層函數的框架暫存器
Lcfi0:
  .cfi_def_cfa_offset 16
Lcfi1:
  .cfi_offset %rbp, -16
  movq	%rsp, %rbp    ## 儲存返回點 (rsp 應該是連結暫存器，在 call 入返回位址)
Lcfi2:
  .cfi_def_cfa_register %rbp
  movl	%edi, -4(%rbp) ## n = edi , edi 是 x86 第一個參數所用的暫存器。
  movl	$0, -8(%rbp)   ## s=0
  movl	$0, -12(%rbp)  ## i=0
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
  movl	-12(%rbp), %eax ## eax = i
  cmpl	-4(%rbp), %eax  ## cmp n i
  jg	LBB0_4            ## if n > i goto LBB0_4
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
  movl	-8(%rbp), %eax  ## eax = s
  addl	-12(%rbp), %eax ## eax = eax + i
  movl	%eax, -8(%rbp)  ## s = eax
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
  movl	-12(%rbp), %eax ## eax = i
  addl	$1, %eax        ## eax ++
  movl	%eax, -12(%rbp) ## i = eax
  jmp	LBB0_1            ## goto LBB0_1
LBB0_4:
  movl	-8(%rbp), %eax  ## eax = s
  popq	%rbp            ## 還原上一層的框架暫存器
  retq                  ## 返回
  .cfi_endproc


.subsections_via_symbols
```

想了解上述 x86 的呼叫過程，請參考：

* [x64函数调用过程分析](https://www.jianshu.com/p/5a4f2d78cb53)

但要了解 x86 的函數呼叫過程，必須先理解『組合語言會怎麼處理多層函數呼叫問題』，請先參考我寫的以 CPU0 為處理器之系統程式書的第三章投影片：

* [陳鍾誠的系統程式書 -- 第 3 章](https://www.slideshare.net/ccckmit/3-73472890)

## main.s 的組合語言解析

```
	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp          ## 儲存上一層函數的框架暫存器
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp    ## 儲存返回點 (rsp 應該是連結暫存器，在 call 入返回位址)
Lcfi2:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp  ## 保留 16 byte 給框架區
	movl	$10, %edi  ## sum 的第一個參數是 10 (gcc x86 固定用 edi 當第一個參數)
	callq	_sum
	leaq	L_.str(%rip), %rdi ## printf 第一個字串參數指標放到 rdi
	movl	%eax, -4(%rbp) ## eax = t
	movl	-4(%rbp), %esi ## t = esi, 所以 t 是 printf 第二個參數
	movb	$0, %al        ## ?? 
	callq	_printf
	xorl	%esi, %esi     ## 把 esi 設為 0
	movl	%eax, -8(%rbp)          ## 4-byte Spill ?? 不知何用？？
	movl	%esi, %eax     ## 把 esi (0) 丟給 eax 傳回
	addq	$16, %rsp      ## 堆疊指標上移 16 byte, 清掉 main 的框架
	popq	%rbp           ## 回復上一層的框架暫存器
	retq                 ## 返回
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"sum(10)=%d\n"


.subsections_via_symbols

```

其中 .cfi_startproc 這些指令是給『除錯器』看的，詳情請參考 DWARF Debugging Information Format

* http://dwarfstd.org/doc/DWARF4.pdf
  * https://sourceware.org/binutils/docs-2.17/as/Pseudo-Ops.html#Pseudo-Ops
  * https://sourceware.org/binutils/docs-2.17/as/CFI-directives.html#CFI-directives
