#include <stdio.h>
#include <stdlib.h>

char *readText(char *fileName) {
  FILE *file = fopen(fileName, "r"); // 開檔
  fseek(file, 0L, SEEK_END);         // 移到檔尾
  int size = ftell(file);            // 取得檔尾位置
  fseek(file, 0L, SEEK_SET);         // 移回檔首
  char *text = malloc(size+1);       // 配置剛好大小的字串空間！
  fread(text, 1, size, file);        // 讀取整個檔案到字串中 
  text[size] = '\0';                 // 設定字串結尾
  fclose(file);                      // 關閉檔案
  return text;                       // 傳回字串
}

int main(int argc, char *argv[]) {
  char *text = readText(argv[1]);    // 讀入整個檔案成為字串
  printf("%s\n", text);              // 印出該字串
  free(text);                        // 釋放該字串的記憶體
}
