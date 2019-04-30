# 函數呼叫的方式

* https://github.com/cccbook/sp/wiki/assemblyCall


## 使用堆疊傳遞參數

1. 在執行 call 指令前，將《參數》推入堆疊
2. 在執行 call 指令時，將《返回點》推入堆疊
3. 在進入函數時，分配框架變數空間
4. 在執行 ret 指令前，恢復框架收回空間
5. 將返回值放在某暫存器 (eax, ....)
6. 執行 ret 返回。

## x86 實作

* https://eli.thegreenplace.net/2011/02/04/where-the-top-of-the-stack-is-on-x86 (x86 讚!)
* https://eli.thegreenplace.net/2011/09/06/stack-frame-layout-on-x86-64/ (x64 讚!)
* [C的function call與stack frame心得](http://lazyflai.blogspot.com/2008/07/cfunction-callstack-frame.html)
* https://www.quora.com/What-is-the-difference-between-a-stack-pointer-and-a-frame-pointer
* https://en.wikipedia.org/wiki/Call_stack

