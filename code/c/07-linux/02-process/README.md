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

```
csienqu-teacher:02-process csienqu$ ./posixSpawn2.exe ls
Run command: ls
Child pid: 2456
README.md       fork3.c         posixSpawn.exe
fork1.c         fork3.exe       posixSpawn2.c
fork1.exe       fork4.c         posixSpawn2.exe
fork2.c         fork4.exe       zombie.c
fork2.exe       posixSpawn.c    zombie.exe
Child exited with status 0

csienqu-teacher:02-process csienqu$ ps
  PID TTY           TIME CMD
  965 ttys000    0:00.01 /bin/bash -l
  789 ttys001    0:00.06 -bash
 2155 ttys002    0:00.01 /bin/bash -l
 2159 ttys003    0:00.02 /bin/bash -l
 2455 ttys003    0:02.67 ./posixSpawn2.exe ls
 2389 ttys004    0:00.01 /bin/bash -l
```

## Fork -- 已被建議不要用，改用 posix_spawn

* https://zh.wikipedia.org/zh-hant/Fork_(%E7%B3%BB%E7%BB%9F%E8%B0%83%E7%94%A8)


```
csienqu-teacher:02-process csienqu$ gcc fork1.c -o fork1.exe
csienqu-teacher:02-process csienqu$ ./fork1.exe
hello!
hello!

csienqu-teacher:02-process csienqu$ gcc fork2.c -o fork2.exe
csienqu-teacher:02-process csienqu$ ./fork2.exe
I am parent process!
I am child process!

csienqu-teacher:02-process csienqu$ gcc fork3.c -o fork3.exe
csienqu-teacher:02-process csienqu$ ./fork3.exe
before fork
I am parent process!
m=100 n=1960
I am child process!
m=100 n=0

csienqu-teacher:02-process csienqu$ ./fork4.exe
before fork
I am parent process!
m=100 n=2062
I am child process!
m=100 n=0
```

```
```