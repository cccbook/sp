# GNU


## ldd


```
$ ldd sum
        ntdll.dll => /c/WINDOWS/SYSTEM32/ntdll.dll (0x7ff9fe050000)
        KERNEL32.DLL => /c/WINDOWS/System32/KERNEL32.DLL (0x7ff9fd140000)
        KERNELBASE.dll => /c/WINDOWS/System32/KERNELBASE.dll (0x7ff9faa20000)
        msys-2.0.dll => /usr/bin/msys-2.0.dll (0x180040000)
```

## strace

```
user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c/03-asm/02-sum
$ strace sum
create_child: sum
--- Process 9920 created
--- Process 9920 loaded C:\Windows\System32\ntdll.dll at 00007ff9fe050000
--- Process 9920 loaded C:\Windows\System32\kernel32.dll at 00007ff9fd140000
--- Process 9920 loaded C:\Windows\System32\KernelBase.dll at 00007ff9faa20000
--- Process 9920 thread 10160 created
--- Process 9920 thread 5240 created
--- Process 9920 loaded C:\msys64\usr\bin\msys-intl-8.dll at 0000000430b30000
--- Process 9920 thread 8816 created
--- Process 9920 loaded C:\msys64\usr\bin\msys-2.0.dll at 0000000180040000
--- Process 9920 loaded C:\msys64\usr\bin\msys-iconv-2.dll at 00000005603f0000
    5       5 [main] sum (9920) **********************************************
  179     184 [main] sum (9920) Program name: C:\msys64\usr\bin\sum.exe (windows pid 9920)
  162     346 [main] sum (9920) OS version:   Windows NT-10.0
  102     448 [main] sum (9920) **********************************************
--- Process 9920 loaded C:\Windows\System32\advapi32.dll at 00007ff9fb4e0000
...
```

## nm

```
user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c/03-asm/02-sum
$ nm sum
...
0000000100408014 I _head_lib64_libkernel32_a
0000000100408000 I _head_msys_2_0_dll
0000000100401190 T _msys_crt0_common
0000000100401580 T _msys_dll_entry
0000000100401640 T _msys_nonmsys_dll_entry
0000000100401660 T _pei386_runtime_relocator
                 U _ZdaPv
                 U _ZdaPvRKSt9nothrow_t
                 U _ZdlPv
                 U _ZdlPvRKSt9nothrow_t
                 U _Znam
                 U _ZnamRKSt9nothrow_t
                 U _Znwm
                 U _ZnwmRKSt9nothrow_t
0000000100401670 T calloc
0000000100401680 T cygwin_internal
0000000100401150 T cygwin_premain0
0000000100401160 T cygwin_premain1
0000000100401170 T cygwin_premain2
0000000100401180 T cygwin_premain3
0000000100401710 T dll_dllcrt0
0000000100407018 b dll_index
0000000100401650 T DllMain
0000000100401690 T free
000000010040812c i fthunk
0000000100401720 T GetModuleHandleA
00000001004080ac i hname
0000000100401080 T main
0000000100401000 T mainCRTStartup
00000001004016a0 T malloc
0000000100408240 I msys_2_0_dll_iname
00000001004016e0 T msys_attach_dll
0000000100401130 T msys_crt0
00000001004016b0 T msys_detach_dll
00000001004016c0 T posix_memalign
0000000100401120 T printf
00000001004016d0 T realloc
0000000100401730 t register_frame_ctor
0000000100407030 b storedHandle
0000000100407020 b storedPtr
0000000100407028 b storedReason
00000001004010c0 T sum
0000000100407040 b u.52910
0000000100401000 T WinMainCRTStartup

```

## size

```
user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c/03-asm/02-sum
$ size sum
   text    data     bss     dec     hex filename
   2817    1964     416    5197    144d sum

```

## xxd

```
user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c/03-asm/02-sum
$ xxd sum
00000000: 4d5a 9000 0300 0000 0400 0000 ffff 0000  MZ..............
00000010: b800 0000 0000 0000 4000 0000 0000 0000  ........@.......
00000020: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000030: 0000 0000 0000 0000 0000 0000 8000 0000  ................
00000040: 0e1f ba0e 00b4 09cd 21b8 014c cd21 5468  ........!..L.!Th
00000050: 6973 2070 726f 6772 616d 2063 616e 6e6f  is program canno
...
```