# JitCall

目前只有在 windows 32 bits 下才能成功，其他系統下會 core dump。

例如在 MinGW64 下會出現下列 jitCall.exe.stackdump

```
Exception: STATUS_ACCESS_VIOLATION at rip=001800BE5B7
rax=0000000100401080 rbx=00000000FFFFCC50 rcx=0000000000000004
rdx=0000000000000020 rsi=0000000100402020 rdi=0000000100401080
r8 =FFFFFFFFFFFFF060 r9 =00000001801429B0 r10=0000000100000000
r11=0000000100401179 r12=0000000000000000 r13=0000000000000000
r14=0000000000000000 r15=0000000000000000
rbp=00000000FFFFCC00 rsp=00000000FFFFCBB8
program=D:\ccc\book\sp\code\c\03-asm\04-jitCall\win64\jitCall.exe, pid 6100, thread main
cs=0033 ds=002B es=002B fs=0053 gs=002B ss=002B
Stack trace:
Frame        Function    Args
000FFFFCC00  001800BE5B7 (000FFFFCDF0, 00000000000, 00000000000, 000FFFFCCB0)
000FFFFCC00  00100401194 (00000000020, 30001000300FF00, 00180047986, 00180046990)
000FFFFCCB0  001800479F7 (00000000000, 00000000000, 00000000000, 00000000000)
00000000000  00180045663 (00000000000, 00000000000, 00000000000, 00000000000)
000FFFFFFF0  00180045714 (00000000000, 00000000000, 00000000000, 00000000000)
End of stack trace
```

這原因可能出在記憶體的對齊與保護模式，因此必須要處理這兩個問題！

在 jserv 的 rubi JIT compiler 中有下列程式碼：

* https://github.com/embedded2015/rubi/blob/master/engine.c

```
void init()
{
    long memsz = 0xFFFF + 1;
    if (posix_memalign((void **) &ntvCode, memsz, memsz))
        perror("posix_memalign");
    if (mprotect(ntvCode, memsz, PROT_READ | PROT_WRITE | PROT_EXEC))
        perror("mprotect");
    tok.pos = ntvCount = 0;
    tok.size = 0xfff;
    set_xor128();
    tok.tok = calloc(sizeof(Token), tok.size);
    brks.addr = calloc(sizeof(uint32_t), 1);
    rets.addr = calloc(sizeof(uint32_t), 1);
}

```

其中 ntvCode 定義在 https://github.com/embedded2015/rubi/blob/master/asm.h

```
unsigned char *ntvCode;
```

上述程式就用 memalign 與 mprotect 處理了這兩個問題。

所以如果要在其他平台跑，必須處理這兩個問題！
