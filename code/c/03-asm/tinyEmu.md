# TinyEMU

* https://github.com/michaelforney/tinyemu

* https://bellard.org/jslinux/
    * 可以直接線上用:

* https://bellard.org/jslinux/vm.html?cpu=riscv64&url=https://bellard.org/jslinux/buildroot-riscv64.cfg&mem=256

```
Loading...
 
Welcome to JS/Linux (riscv64)
 
Use 'vflogin username' to connect to your account.
You can create a new account at https://vfsync.org/signup .
Use 'export_file filename' to export a file to your computer.
Imported files are written to the home directory.
 
[root@localhost ~]# ls
bench.py       hello.c        readme.txt     rv128test.bin
[root@localhost ~]# gcc -S hello.c -o hello.s
[root@localhost ~]# ls
bench.py       hello.c        hello.s        readme.txt     rv128test.bin
[root@localhost ~]# cat hello.s
        .file   "hello.c"
        .option nopic
        .text
        .section        .rodata
        .align  3
.LC0:
        .string "Hello World"
        .text
        .align  1
        .globl  main
        .type   main, @function
main:
        add     sp,sp,-32
        sd      ra,24(sp)
        sd      s0,16(sp)
        add     s0,sp,32
        mv      a5,a0
        sd      a1,-32(s0)
        sw      a5,-20(s0)
        lui     a5,%hi(.LC0)
        addi    a0,a5,%lo(.LC0)
        call    puts
        li      a5,0
        mv      a0,a5
        ld      ra,24(sp)
        ld      s0,16(sp)
        add     sp,sp,32
        jr      ra
        .size   main, .-main
        .ident  "GCC: (GNU) 7.3.0"
[root@localhost ~]# ls
bench.py       hello.c        hello.s        readme.txt     rv128test.bin
[root@localhost ~]#

```