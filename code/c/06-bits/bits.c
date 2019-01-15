// 參考: https://github.com/cccbook/bottomupcs/wiki/02-binary

#include <stdio.h>

int main(int argc, char *argv[])
{
   unsigned char mask = 0x0F;
   unsigned char data = 0xA5;
   unsigned char maskData = mask & data;
   printf("%02x & %02x = %02x\n", data, mask, maskData);
}
