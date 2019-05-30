

## coredump.c

```
csienqu-teacher:05-memory csienqu$ gcc coredump.c -o coredump.exe
csienqu-teacher:05-memory csienqu$ ./coredump.exe
Segmentation fault: 11
```

## struct.c

```
sienqu-teacher:05-memory csienqu$ gcc struct.c -o struct.exe
csienqu-teacher:05-memory csienqu$ ./struct.exe
0x7ffee61309a0 : s.char_one
0x7ffee61309a1 : s.char_two
0x7ffee61309a4 : s.int_one

csienqu-teacher:05-memory csienqu$ gcc -fpack-struct -o struct-packed.exe struct.c
csienqu-teacher:05-memory csienqu$ ./struct-packed.exe
0x7ffee9a0e990 : s.char_one
0x7ffee9a0e991 : s.char_two
0x7ffee9a0e992 : s.int_one
```