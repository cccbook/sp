# 組合語言解讀

## 工具

* [gdb](gdb.md)
    * https://linuxtools-rst.readthedocs.io/zh_CN/latest/tool/gdb.html

## Frame 

* https://eli.thegreenplace.net/2011/02/04/where-the-top-of-the-stack-is-on-x86 (x86 讚!)
* https://eli.thegreenplace.net/2011/09/06/stack-frame-layout-on-x86-64/ (x64 讚!)
* [C的function call與stack frame心得](http://lazyflai.blogspot.com/2008/07/cfunction-callstack-frame.html)
* https://www.quora.com/What-is-the-difference-between-a-stack-pointer-and-a-frame-pointer
* https://en.wikipedia.org/wiki/Call_stack

## x86

* https://eli.thegreenplace.net/2011/02/04/where-the-top-of-the-stack-is-on-x86 (x86 讚!)


Herein lies the source of the confusion. Intel's x86 architecture places its stack "head down". It starts at some address and grows down to a lower address. Here's how it looks:

![](https://eli.thegreenplace.net/images/2011/02/stack1.png)

So when we say "top of the stack" on x86, we actually mean the lowest address in the memory area occupied by the stack. This may be unnatural for some people [2]. As long as we keep the diagram shown above firmly in mind, however, we should be OK.

```
int foobar(int a, int b, int c)
{
    int xx = a + 2;
    int yy = b + 3;
    int zz = c + 4;
    int sum = xx + yy + zz;

    return xx * yy * zz + sum;
}

int main()
{
    return foobar(77, 88, 99);
}
```

![](https://eli.thegreenplace.net/images/2011/02/stackframe1.png)



## x64

* https://eli.thegreenplace.net/2011/09/06/stack-frame-layout-on-x86-64/ (x64 讚!)

```
long utilfunc(long a, long b, long c)
{
    long xx = a + 2;
    long yy = b + 3;
    long zz = c + 4;
    long sum = xx + yy + zz;

    return xx * yy * zz + sum;
}
```

![](https://eli.thegreenplace.net/images/2011/08/x64_frame_leaf.png)
