# GCC

## 產生組合語言

```
$ gcc -S sum.c -o sum.s
```

## 將組合語言轉換為目的碼 (Object Code)

```
$ gcc -c sum.s -o sum.o
```

## 將目的碼與函式庫連結後產生執行檔

```
$ gcc sum.o -o sum
$ ./sum
sum(10)=55
```

## 反組譯目的碼

```
PS D:\ccc\book\sp\code\c\01-gcc\01-toolchain> objdump -d sum.o

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

0000002d <_main>:
  2d:   55                      push   %ebp
  2e:   89 e5                   mov    %esp,%ebp
  30:   83 e4 f0                and    $0xfffffff0,%esp
  33:   83 ec 20                sub    $0x20,%esp
  36:   e8 00 00 00 00          call   3b <_main+0xe>
  3b:   c7 04 24 0a 00 00 00    movl   $0xa,(%esp)
  42:   e8 b9 ff ff ff          call   0 <_sum>
  47:   89 44 24 1c             mov    %eax,0x1c(%esp)
  4b:   8b 44 24 1c             mov    0x1c(%esp),%eax
  4f:   89 44 24 04             mov    %eax,0x4(%esp)
  53:   c7 04 24 00 00 00 00    movl   $0x0,(%esp)
  5a:   e8 00 00 00 00          call   5f <_main+0x32>
  5f:   b8 00 00 00 00          mov    $0x0,%eax
  64:   c9                      leave
  65:   c3                      ret
  66:   90                      nop
  67:   90                      nop
```

