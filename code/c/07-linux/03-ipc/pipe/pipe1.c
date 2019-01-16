// https://gist.github.com/yangl1996/a8f4edf7b50e1d1759fc092cd7abcc8b
/*
 * Linux IPC via pipe()
 *
 * By Lei Yang <leiyang@fastmail.com>
 * March 20, 2017
 *
 * Expected output: Message from the parent: Hello from the the parent!
 *
 * Released under WTFPL 2.0
 */


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int fid[2] = {0};
    int result = pipe(fid);
    if (result != 0)
    {
        printf("Failed to create pipe 0.0\n");
    }
    
    pid_t childid;
    childid = fork();
    if (childid == -1)
    {
        printf("Failed to fork 0.0\n");
    }

    /* divergent */
    if (childid == 0)
    {
        /* child */
        close(fid[1]); /* child closes the write end */
        char buffer[50];
        read(fid[0], buffer, sizeof(buffer));
        printf("Message from the parent: %s", buffer);
        exit(0);
    }
    else
    {
        /* parent */
        close(fid[0]); /* parent closes the read end */
        char towrite[] = "Hello from the the parent!\n";
        write(fid[1], towrite, strlen(towrite) + 1);
        exit(0);
    }
    return 0;
}