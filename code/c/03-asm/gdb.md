# gdb 除錯工具


## 編譯 (必須加上 -g)

```
user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c/03-asm/02-sum
$ gcc main.c sum.c -o sum -g

user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c/03-asm/02-sum
$ gdb sum
Reading symbols from sum...done.
$ layout split // 這會出現《原始碼+組合語言》視窗

```

## gdb交互命令

參考: https://linuxtools-rst.readthedocs.io/zh_CN/latest/tool/gdb.html#

```
r: run
c: continue
n: next 會跳過函數
s: step 會進入函數
q: quit
break n （简写b n）:在第n行处设置断点
（可以带上代码路径和代码名称： b OAGUPDATE.cpp:578）
delete breakpoints：清除所有断点：
print a：将显示整数 a 的值
layout src：显示源代码窗口
layout split：显示源代码和反汇编窗口
```
