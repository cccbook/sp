// 參考 -- https://github.com/cccbook/bottomupcs/wiki/05-process
// windows 中請在 MSYS2 裏執行！

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int signum)
{
        printf("got SIGINT\n");
}

int main(void)
{
        signal(SIGINT, sigint_handler);
        printf("pid is %d\n", getpid());
        while (1)
                sleep(1);
}

/* 執行結果

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/13-signal
$ gcc signal1.c -o signal1

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/13-signal
$ ./signal1
pid is 8220
got SIGINT
got SIGINT
got SIGINT
got SIGINT
got SIGINT
got SIGINT
got SIGINT
got SIGINT
got SIGINT
got SIGINT
got SIGINT

[1]+  已停止               ./signal1

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/13-signal
$ kill -SIGINT 8220

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/13-signal
$ fg
./signal1
got SIGINT
Quit (核心已傾印)

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/13-signal
$ ps
      PID    PPID    PGID     WINPID   TTY         UID    STIME COMMAND
     4660       1    4660       4660  ?         197609 10:01:34 /usr/bin/mintty
     9788    8484    9788      10880  pty0      197609 10:06:46 /usr/bin/ps
     8484    4660    8484      10044  pty0      197609 10:01:35 /usr/bin/bash

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/13-signal
$ ls
signal1.c  signal1.exe  signal1.exe.stackdump

*/