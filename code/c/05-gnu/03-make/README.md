# Makefile

```
$@ : 該規則的目標文件 (Target file)
$* : 代表 targets 所指定的檔案，但不包含副檔名
$< : 依賴文件列表中的第一個依賴文件 (Dependencies file)
$^ : 依賴文件列表中的所有依賴文件
$? : 依賴文件列表中新於目標文件的文件列表
$* : 代表 targets 所指定的檔案，但不包含副檔名

?= 語法 : 若變數未定義，則替它指定新的值。
:= 語法 : make 會將整個 Makefile 展開後，再決定變數的值。
```

## 範例 1 ：

```
%.o: %.c
    gcc -c $< -o $@

$< : 屬於第一條件，也就是 foo.c
$@ : 屬於目標條件，也就是 foo.o
```

## 範例 2 : https://github.com/jserv/mini-arm-os/blob/master/07-Threads/Makefile


* [EricWang: makefile 心得、教學](https://wwssllabcd.github.io/blog/2016/10/03/how-to-write-make-file/)
