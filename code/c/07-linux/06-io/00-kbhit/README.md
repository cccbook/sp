# kbhit


這個程式必須在 windows 裡使用，並且不能用 MSYS2 。


```
PS D:\ccc\book\sp\code\c\07-linux\06-io\00-kbhit-windows> gcc kbhit.c -o kbhit
PS D:\ccc\book\sp\code\c\07-linux\06-io\00-kbhit-windows> ./kbhit
a
d
x
z
c
a

?
v
```

在 linux 底下必須自己寫程式，方法不同。

* http://www.flipcode.com/archives/_kbhit_for_Linux.shtml

而且 MSYS2 底下由於沒有 stropts.h， 所以不能用！

```
/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>

int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

//////////////////////////////////////////////
//    Simple demo of _kbhit()

#include <unistd.h>

int main(int argc, char** argv) {
    printf("Press any key");
    while (! _kbhit()) {
        printf(".");
        fflush(stdout);
        usleep(1000);
    }
    printf("\nDone.\n");

    return 0;
} 
```