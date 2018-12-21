
## call 的 bug

  printf("sum(10)=%d\n", sum(10));

會造成 arg 亂掉！

```
# arg      _Str4                      # $_Str4                     # 0       
	movl $_Str4, %eax
	movl %eax, 0(%esp)
# arg      10                         # 10                         # 1       
	movl $10, %eax
	movl %eax, 4(%esp)
# local    t0                         # t0                         # L0      
# call     t0       sum               # L0       _sum              #         
	call _sum
	movl %eax, -4(%ebp)
# arg      t0                         # L0                         # 0       
	movl -4(%ebp), %eax
	movl %eax, 0(%esp)
# local    t1                         # t1                         # L1      
# call     t1       printf            # L1       _printf           #         
	call _printf
```

解決方法: 在 char *CALL(char *id) 裏最後才產生 arg 就行了

```c
char *CALL(char *id) {
  ...
  for (int i=0; i<top; i++) {
    vmCode("arg", args[i], "", "");
  }
  ...
}
```

## frame size 的 bug

在 x86.c 當中，subl $%d, %esp 應該減多少？按理說應該是 fLocalTop*4 + 4 ，但卻會當掉。

```
    xEmit("	.text\n	.globl	_%s\n	.def	%s;	.scl	2;	.type	32;	.endef\n_%s:\n", d, d, d, d);
    xEmit("	pushl	%%ebp\n	movl	%%esp, %%ebp\n");
    int fLocalTop = atoi(_p2);
    xEmit("	subl	$%d, %%esp\n", fLocalTop*4 + 16); // 加少一點 (8) 不行，會掛掉？為何？ 按理講應該只需要加 saved ebp 的 4 byte 就行了阿?
```

原因應該是函數裏若有 call 其他函數，那麼那些函數的參數也需要框架空間！  (另外還要考慮 call 時的 return address)，所以程式修正如下。

```
    int argSize = argTop + 1; // +1 存放 return address
    int frameSize = MAX(localTop, argSize) + 1; // +1 存放 saved ebp
    fCode->_p2 = stPrint("%d", frameSize);
```

修改後 suml.c 測試成功!

## 參數的 bug

在 suml.c 當中，int sum(int n) 的參數 n 在函數裏，應該用  8(%ebp) 存取才對

```
#  arg n  
	movl 8(%ebp), %eax
	movl %eax, 12(%esp)
```

?? 為何是  8(%ebp) ???

解答參考: https://eli.thegreenplace.net/2011/02/04/where-the-top-of-the-stack-is-on-x86

因為 

1. ebp 指向 saved ebp;
2. 4(%ebp) 指向 return address
3. 8(%ebp) 指向 第一個參數

此 bug 修改掉了!






