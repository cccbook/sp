# Nand2tetris : HackCPU Virtual Machine (VM)


```
user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/03-nand2tetris/vm
$ ls
vm.c

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/03-nand2tetris/vm
$ gcc vm.c -o vm

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/03-nand2tetris/vm
$ ./vm test/Add.bin

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/03-nand2tetris/vm
$ ./vm ../test/Add.bin
PC=0000 I=0002 A=0001 D=0002 m[A]=0000
PC=0001 I=EC10 A=0002 D=0002 m[A]=0002 a=0 c=30 d=2 j=0
PC=0002 I=0003 A=0003 D=0003 m[A]=0002
PC=0003 I=E090 A=0004 D=0003 m[A]=0005 a=0 c=02 d=2 j=0
PC=0004 I=0000 A=0005 D=0000 m[A]=0005
PC=0005 I=E308 A=0006 D=0000 m[A]=0005 a=0 c=0C d=1 j=0
exit program !
```