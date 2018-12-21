#include <search.h>                                        // 引用檔案 search.h
#include <stdlib.h>                                        
#include <stdio.h>                                         
#include <string.h>

char *names[] = { "George", "Mary",                        // 宣告名單
"Bob", "Snoopy", "Mickey", "John", "Mike" };               

typedef struct {                                           // 宣告結構 person
  char *name;                                               
  int  id;                                                   
} person;                                                   

#define person_print(p) printf("id=%d name=%s\n", p->id, p->name)                   

int compare(const void *pa, const void *pb) {              // 定義比較函數
  person *p1=(person*)pa, *p2=(person*)pb;                   
  return strcmp(p1->name, p2->name);                       
}                                                           

void action(const void *nodep, const VISIT which,          // 定義節點訪問動作
            const int depth) {                               
  person *p;                                               
  switch(which) {                                           
    case preorder:                                           
      break;                                               
    case postorder:                                           
      p = *(person**)nodep;                                   
      person_print(p);                                       
      break;                                               
    case endorder:                                           
      break;                                               
    case leaf:                                               
      p = *(person**)nodep;                                   
      person_print(p);                                       
      break;                                               
  }                                                           
}                                                           

void binaryTreeTest() {                                    // 二元樹測試程式
  void *v, *root=NULL;                                     // 宣告根節點
  int i;                                                   
  for (i = 0; i < 7; i++) {                                // 將名單加入樹中
    person *p = (person*) malloc(sizeof(person));          // 分配空間
    p->name = strdup(names[i]);                            // 複製名稱
    p->id = i;                                             // 設定編號
    v = tsearch((void *)p, &root, compare);                // 新增p記錄
  }                                                           
  twalk(root, action);                                     // 列印整顆樹
}                                                           

void hashTableTest() {                                     // HashTable 測試程式
  void *v;                                                   
  int i;                                                   
  ENTRY e, *ep;                                               

  hcreate(30);                                             // 建立 hashTable
  for (i = 0; i < 5; i++) {                                // 將名單放入表格
    person *p = (person*) malloc(sizeof(person));          // 分配空間
    p->name = strdup(names[i]);                            // 複製名稱
    p->id = i;                                             // 設定編號
    e.key = p->name;                                       // 設定e=(key, data)
    e.data = p;                                               
    v = hsearch(e, ENTER);                                 // 新增e記錄
  }                                                           
  for (i=0; i<7; i++) {                                    // 從表格中取出名單
    e.key = names[i];                                      // 設定搜尋的 key
    ep = hsearch(e, FIND);                                 // 開始搜尋
    if (ep != NULL) {                                      // 如果有找到
      person *p = ep->data;                                //   取得 person
      person_print(p);                                     //   列印 person
    } else                                                 // 否則
      printf("%s not found !\n", e.key);                   //   印出找不到
  }                                                           
  hdestroy();                                              // 刪除 HashTable
}                                                           

int main() {                                               // 主程式
  printf("=====binaryTreeTest()=======\n");                   
  binaryTreeTest();                                        // 測試二元樹
  printf("=====hashTableTest()=======\n");                   
  hashTableTest();                                         // 測試 HashTable
  return 0;
}