// 參考 -- https://github.com/cccbook/bottomupcs/wiki/07-toolchain
// windows 中請在 MSYS2 裏執行！

#include <stdio.h>

struct a_struct {
        char char_one;
        char char_two;
        int int_one;
};

int main(void)
{

        struct a_struct s;

        printf("%p : s.char_one\n" \
               "%p : s.char_two\n" \
               "%p : s.int_one\n", &s.char_one,
               &s.char_two, &s.int_one);

        return 0;

}

/* 執行結果

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/14-memory
$ ls
struct.c

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/14-memory
$ gcc struct.c -o struct

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/14-memory
$ ./struct
0xffffcbf8 : s.char_one
0xffffcbf9 : s.char_two
0xffffcbfc : s.int_one

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/14-memory
$ gcc -fpack-struct -o struct-packed struct.c

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/14-memory
$ ./struct-packed
0xffffcbfa : s.char_one
0xffffcbfb : s.char_two
0xffffcbfc : s.int_one

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/14-memory
*/