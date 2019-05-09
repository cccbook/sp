# Process

## posix_spawn

* [多进程编程函数posix_spawn实例](https://blog.csdn.net/Linux_ever/article/details/50295105)
* [linux posix_spawn](https://blog.csdn.net/yiwuxue/article/details/22189685) (讚!)

```
user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c/07-linux/02-process
$ gcc posixSpawn.c -o posixSpawn

user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c/07-linux/02-process
$ ./posixSpawn ls
Run command: ls
Child pid: 9868
fork.exe  fork1.exe  fork2.exe  fork3.exe     posixSpawn.exe  zombie.c
fork1.c   fork2.c    fork3.c    posixSpawn.c  README.md       zombie.exe
Child exited with status 0
```

## Fork -- 已被建議不要用，改用 posix_spawn

* https://zh.wikipedia.org/zh-hant/Fork_(%E7%B3%BB%E7%BB%9F%E8%B0%83%E7%94%A8)