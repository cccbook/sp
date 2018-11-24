#ifndef ARRAY_H
#define ARRAY_H

#include "Lib.h"

typedef struct {
  int size;    // 陣列目前的上限 
  int count;   // 陣列目前的元素個數 
  void **item; // 每個陣列元素的指標
} Array;       // 動態陣列的資料結構 

typedef enum { KEEP_SPLITER, REMOVE_SPLITER } SplitMode;

extern void ArrayTest();

extern Array* ArrayNew(int size);// 建立新陣列 
extern void ArrayFree(Array *array, FuncPtr1 freeFuncPtr); // 釋放該陣列 
extern void ArrayAdd(Array *array, void *item); // 新增一個元素 
extern void ArrayPush(Array *array,void *item); // (模擬堆疊) 推入一個元素 
extern void* ArrayPop(Array *array);  //(模擬堆疊) 彈出一個元素  
extern void* ArrayPeek(Array *array); //(模擬堆疊) 取得最上面的元素 
extern void* ArrayLast(Array *array); // 取得最後一個元素 
extern void ArrayEach(Array *array, FuncPtr1 f); //對每個元素都執行 f 函數 

extern Array* split(char *str, char *spliter, SplitMode mode);

#endif
