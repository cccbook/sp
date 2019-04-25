#include <stdio.h>
#include <conio.h> /* getch() and kbhit() */
int main()
{
    char c;
    while (1) {
        if(kbhit()){
            c = getch();
            printf("%c\n", c);
        }
    }
    return 0;
}