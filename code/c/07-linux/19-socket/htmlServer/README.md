# HelloWebServer

修改來源 -- http://rosettacode.org/wiki/Hello_world/Web_server#C


## helloWebServer.c

```
$ gcc helloWebServer.c -o helloWebServer
$ ./helloWebServer
```

然後你會看到一個只會說 hello world! 的 server

## headPrintServer.c

```
$ gcc headPrintServer.c -o headPrintServer
$ ./headPrintServer
```

一樣只會說 hello world! 

但會印出 http header 方便觀察！

## htmlServer

```
$ gcc htmlServer.c -o htmlServer
$ ./htmlServer
```

然後訪問 http://localhost:8080/index.html 可以看到網頁，任意點選連結訪問其他頁面！

## threadServer

```
$ gcc threadServer.c -o threadServer
$ ./threadServer
```

這版功能和 htmlServer 一樣，但是使用 multi thread 可以快速應付更多的請求 (流量)！

