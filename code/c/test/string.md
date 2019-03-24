# <string.h> - C語言標準庫

* http://tw.gitbook.net/c_standard_library/string_h.html

* strpbrk() :  (String Pointer Break)
    * strpbrk("012345a78b", "ab") 會傳回 a78b 的指標。
* strspn() : strspn("ABCDEFG019874", "ABCD") == 4
    * http://tw.gitbook.net/c_standard_library/c_function_strspn.html
* strxfrm() : 複製字串 len = strxfrm(dest, "0123456789", 5);       dest = "01234"
    * 類似 strcpy, 但不需要再自己設最後的 \0

Function & Description
1	void *memchr(const void *str, int c, size_t n)
Searches for the first occurrence of the character c (an unsigned char) in the first n bytes of the string pointed to, by the argument str.

2	int memcmp(const void *str1, const void *str2, size_t n)
Compares the first n bytes of str1 and str2.

3	void *memcpy(void *dest, const void *src, size_t n)
Copies n characters from src to dest.

4	void *memmove(void *dest, const void *src, size_t n)
Another function to copy n characters from str2 to str1.

5	void *memset(void *str, int c, size_t n)
Copies the character c (an unsigned char) to the first n characters of the string pointed to, by the argument str.

6	char *strcat(char *dest, const char *src)
Appends the string pointed to, by src to the end of the string pointed to by dest.

7	char *strncat(char *dest, const char *src, size_t n)
Appends the string pointed to, by src to the end of the string pointed to, by dest up to n characters long.

8	char *strchr(const char *str, int c)
Searches for the first occurrence of the character c (an unsigned char) in the string pointed to, by the argument str.

9	int strcmp(const char *str1, const char *str2)
Compares the string pointed to, by str1 to the string pointed to by str2.

10	int strncmp(const char *str1, const char *str2, size_t n)
Compares at most the first n bytes of str1 and str2.

11	int strcoll(const char *str1, const char *str2)
Compares string str1 to str2. The result is dependent on the LC_COLLATE setting of the location.

12	char *strcpy(char *dest, const char *src)
Copies the string pointed to, by src to dest.

13	char *strncpy(char *dest, const char *src, size_t n)
Copies up to n characters from the string pointed to, by src to dest.

14	size_t strcspn(const char *str1, const char *str2)
Calculates the length of the initial segment of str1 which consists entirely of characters not in str2.

15	char *strerror(int errnum)
Searches an internal array for the error number errnum and returns a pointer to an error message string.

16	size_t strlen(const char *str)
Computes the length of the string str up to but not including the terminating null character.

17	char *strpbrk(const char *str1, const char *str2)
Finds the first character in the string str1 that matches any character specified in str2.

18	char *strrchr(const char *str, int c)
Searches for the last occurrence of the character c (an unsigned char) in the string pointed to by the argument str.

19	size_t strspn(const char *str1, const char *str2)
Calculates the length of the initial segment of str1 which consists entirely of characters in str2.

20	char *strstr(const char *haystack, const char *needle)
Finds the first occurrence of the entire string needle (not including the terminating null character) which appears in the string haystack.

21	char *strtok(char *str, const char *delim)
Breaks string str into a series of tokens separated by delim.

22	size_t strxfrm(char *dest, const char *src, size_t n)
Transforms the first n characters of the string src into current locale and places them in the string dest.