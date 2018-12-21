# Hello Risc-V

```
$ cd code
$ cd 01-hello/
$ ls
hello.c
$ riscv64-unknown-elf-gcc -O2 -o hello.o hello.c
$ spike pk hello.o
bbl loader
Hello RISC-V
```

## 組合語言

```
$ riscv64-unknown-elf-gcc -S -o hello.s hello.c
```

hello.s

```
	.file	"hello.c"
	.option nopic
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"Hello RISC-V"
	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32
	mv	a5,a0
	sd	a1,-32(s0)
	sw	a5,-20(s0)
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	puts
	li	a5,0
	mv	a0,a5
	ld	ra,24(sp)
	ld	s0,16(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 8.2.0"
```

