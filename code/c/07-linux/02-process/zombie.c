// 參考 https://github.com/cccbook/bottomupcs/wiki/05-process
// windows 中請在 MSYS2 裏執行！

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void)
{
        pid_t pid;

        printf("parent : %d\n", getpid());

        pid = fork();

        if (pid == 0) {
                printf("child : %d\n", getpid());
                sleep(2);
                printf("child exit\n");
                exit(1);
        }

        /* in parent */
        while (1)
        {
                sleep(1);
        }
}

/* 執行結果

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/12-process
$ gcc zombie.c -o zombie

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/12-process
$ ./zombie
parent : 8160
child : 6516
child exit

*/