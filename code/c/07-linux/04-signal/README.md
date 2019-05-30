
```
csienqu-teacher:04-signal csienqu$ gcc signal1.c -o signal1.exe
csienqu-teacher:04-signal csienqu$ ./signal1.exe
pid is 1125
^Cgot SIGINT
^Cgot SIGINT
^Cgot SIGINT
^Cgot SIGINT
^Cgot SIGINT
^Cgot SIGINT
Terminated: 15
csienqu-teacher:04-signal csienqu$ 
```

用 kill 砍掉

```
csienqu-teacher:shm csienqu$ ps
  PID TTY           TIME CMD
  647 ttys000    0:00.01 /bin/bash -l
  810 ttys001    0:00.02 /bin/bash -l
 1125 ttys001    0:00.00 ./signal1.exe
  888 ttys002    0:00.01 /bin/bash -l
csienqu-teacher:shm csienqu$ kill 1125
```


