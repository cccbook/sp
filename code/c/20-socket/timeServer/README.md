# Simple Socket Client/Server

來源 -- https://gist.github.com/browny/5211329

```
gcc server.c -o server
gcc client.c -o client
./server
./client 127.0.0.1
```

背景執行 server

```
user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/20-socket/timeServer
$ ./server &
[1] 7904

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/20-socket/timeServer
$ ./client

 Usage: ./client <ip of server>

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/20-socket/timeServer
$ ./client 127.0.0.1
Tue Jan 15 14:51:54 2019

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/20-socket/timeServer
$ ./client 127.0.0.1
Tue Jan 15 14:51:56 2019

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/20-socket/timeServer
$ ./client 127.0.0.1
Tue Jan 15 14:51:58 2019

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/20-socket/timeServer
$ ./client 127.0.0.1
Tue Jan 15 14:52:00 2019

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/20-socket/timeServer
$ ps
      PID    PPID    PGID     WINPID   TTY         UID    STIME COMMAND
    10180    8484   10180       9340  pty0      197609 14:52:01 /usr/bin/ps
     4660       1    4660       4660  ?         197609 10:01:34 /usr/bin/mintty
     7904    8484    7904       8132  pty0      197609 14:51:45 /d/ccc/book/sp/code/c/20-socket/timeServer/server
     8484    4660    8484      10044  pty0      197609 10:01:35 /usr/bin/bash

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/20-socket/timeServer
$

```