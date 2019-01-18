# 編譯優化

1. 使用 gcc -O3 可達最高等級優化 
2. Pointer Aliasing會讓編譯器最佳化功能無用武之地。 
    * 以下範例來自 [Jserv :你所不知道的 C 語言：編譯器和最佳化原理篇](https://hackmd.io/s/Hy72937Me?fbclid=IwAR0kBKYy6sfren5Sd_c0iC4aryssu-ZgLEJ7X6ql8F65awanDYfq91PaOUc)

```
Pointer Aliasing會讓編譯器最佳化功能無用武之地。
針對下面程式碼
void foo(int *i1, int *i2, int *res)
{
    for (int i = 0; i < 10; i++) {
        *res += *i1 + *i2;
    }
}
可能一開始會想優化成下面這樣來加速
void foo(int *i1, int *i2, int *res)
{
    int tmp = *i1 + *i2;
    for (int i = 0; i < 10; i++) {
        *res += tmp;
    }
}
但若考慮到有人這樣寫 foo(&var, &var, &var) 來呼叫 foo()，那很明顯就會發生問題了，*res 值的改變影響 *i1、*i2。所以 Compiler 不會這樣最佳化，因為不知道 caller 會怎麼傳遞數值。
切到 Compiler Analysis
```

## 參考文獻
* [你所不知道的 C 語言：編譯器和最佳化原理篇](https://hackmd.io/s/Hy72937Me?fbclid=IwAR0kBKYy6sfren5Sd_c0iC4aryssu-ZgLEJ7X6ql8F65awanDYfq91PaOUc)