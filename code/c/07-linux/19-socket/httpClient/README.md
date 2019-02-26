# httpClient.c

* 來源 -- [鄭中勝: 以 C Socket 實作 HTTP Client](https://notfalse.net/47/c-socket-http-client)
    * https://github.com/JS-Zheng/blog/blob/master/47.%20C%20Socket%20HTTP%20Client/main.c

## 執行

在 MSYS2/MinGW64 中

```
user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/07-linux/19-socket/httpClient
$ gcc httpClient.c -o httpClient

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/07-linux/19-socket/httpClient
$ ./httpClient
----------
Request:
----------
GET / HTTP/1.1
Host: example.com


----------
Response:
----------
HTTP/1.1 200 OK
Accept-Ranges: bytes
Cache-Control: max-age=604800
Content-Type: text/html; charset=UTF-8
Date: Tue, 26 Feb 2019 00:50:55 GMT
Etag: "1541025663+gzip"
Expires: Tue, 05 Mar 2019 00:50:55 GMT
Last-Modified: Fri, 09 Aug 2013 23:54:35 GMT
Server: ECS (sjc/4E8B)
Vary: Accept-Encoding
X-Cache: HIT
Content-Length: 1270

<!doctype html>
<html>
<head>
    <title>Example Domain</title>

    <meta charset="utf-8" />
    <meta http-equiv="Content-type" content="text/html; charset=utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <style type="text/css">
    body {
        background-color: #f0f0f2;
        margin: 0;
        padding: 0;
        font-family: "Open Sans", "Helvetica Neue", Helvetica, Arial, sans-serif;

    }
    div {
        width: 600px;
        margin: 5em auto;
        padding: 50px;
        background-color: #fff;
        border-radius: 1em;
    }
    a:link, a:visited {
        color: #38488f;
        text-decoration: none;
    }
    @media (max-width: 700px) {
        body {
            background-color: #fff;
        }
        div {
            width: auto;
            margin: 0 auto;
            border-radius: 0;
            padding: 1em;
        }
    }
    </style>
</head>

<body>
<div>
    <h1>Example Domain</h1>
    <p>This domain is established to be used for illustrative examples in documents. You may use this
    domain in examples without prior coordination or asking for permission.</p>
    <p><a href="http://www.iana.org/domains/example">More information...</a></p>
</div>
</body>
</html>


```

## 第 0 版

上述程式簡化後變成 httpClient0.c

## 修改過後的 httpClient2recvPart.c

這版只會接收一個封包，因此對很長的網頁會顯示不完整！

```
$ ./httpClient2recvPart misavo.com /view/ccc/README.md
----------
Request:
----------
GET /view/ccc/README.md HTTP/1.1
Host: misavo.com


----------
Response:
----------
HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: 7458
Date: Tue, 26 Feb 2019 01:07:47 GMT
Connection: keep-alive

<!doctype html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Home of C.C.Chen=陳鍾誠的網站 >>  陳鍾誠</title>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/pure/0.6.2/pure-min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <link rel="stylesheet" href="../../mdbook.css">
</head>
<body>

<div class="header pure-menu pure-menu-horizontal">
  <ul id="topBar" class="pure-menu-list">
    <li id="bookTitle" class="pure-menu-item"></li>
    <i onclick="MDB.view()" class="fa fa-tablet" aria-hidden="true" title="View"></i>&nbsp;
    <i onclick="MDB.edit()" class="fa fa-pencil-square-o" aria-hidden="true" title="Edit"></i>&nbsp;
<!--    <i onclick="MDB.save()" class="fa fa-floppy-o" aria-hidden="true" title="Save"></i>&nbsp; -->
    <i onclick="MDB.plugin('upload.html')" class="fa fa-upload" aria-hidden="true" title="Upload"></i>
    <li id="opMenu" class="pure-menu-item pure-menu-has-children pure-menu-allow-hover">
      <a id="me" class="pure-menu-link mt" data-mt="User"></a>
      <ul class="pure-menu-children">
        <li class="pure-menu-item"><a onclick="MDB.plugin('createBook.html')" class="pure-menu-link

```

## 繼續修正後的 httpClient2recvAll.c

這版會接收一連串封包，因此對很長的網頁還是可以完整顯示！

```
user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/07-linux/19-socket/httpClient
$ gcc httpClient3recvAll.c -o httpClient3recvAll

user@DESKTOP-96FRN6B MINGW64 /d/ccc/book/sp/code/c/07-linux/19-socket/httpClient
$ ./httpClient3recvAll misavo.com /view/ccc/README.md
----------
Request:
----------
GET /view/ccc/README.md HTTP/1.1
Host: misavo.com


packetLen=1460
----------
Response:
----------
HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: 7458
Date: Tue, 26 Feb 2019 01:22:45 GMT
Connection: keep-alive

<!doctype html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Home of C.C.Chen=陳鍾誠的網站 >>  陳鍾誠</title>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/pure/0.6.2/pure-min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <link rel="stylesheet" href="../../mdbook.css">
</head>
<body>

<div class="header pure-menu pure-menu-horizontal">
  <ul id="topBar" class="pure-menu-list">
    <li id="bookTitle" class="pure-menu-item"></li>
    <i onclick="MDB.view()" class="fa fa-tablet" aria-hidden="true" title="View"></i>&nbsp;
    <i onclick="MDB.edit()" class="fa fa-pencil-square-o" aria-hidden="true" title="Edit"></i>&nbsp;
<!--    <i onclick="MDB.save()" class="fa fa-floppy-o" aria-hidden="true" title="Save"></i>&nbsp; -->
    <i onclick="MDB.plugin('upload.html')" class="fa fa-upload" aria-hidden="true" title="Upload"></i>
    <li id="opMenu" class="pure-menu-item pure-menu-has-children pure-menu-allow-hover">
      <a id="me" class="pure-menu-link mt" data-mt="User"></a>
      <ul class="pure-menu-children">
        <li class="pure-menu-item"><a onclick="MDB.plugin('createBook.html')" class="pure-menu-link
packetLen=1460
----------
Response:
----------
 mt" data-mt="NewBook=寫書">NewBook</a></li>
        <li class="pure-menu-item"><a onclick="MDB.plugin('login.html')" class="pure-menu-link mt" data-mt="Login=登入">Login</a></li>
        <li class="pure-menu-item"><a onclick="MDB.logout()" class="pure-menu-link mt" data-mt="Logout=登出">Logout</a></li>
<!--        <li class="pure-menu-item"><a onclick="MDB.plugin('search.html')" class="pure-menu-link mt" data-mt="Search=搜尋">Search</a></li>
        <li class="pure-menu-item"><a href="#sms" class="pure-menu-link mt" data-mt="Comment=留言">Comment</a></li>
-->
      </ul>
    </li>
    <li id="languageMenu" class="pure-menu-item pure-menu-has-children pure-menu-allow-hover"> <!-- hidden -->
      <a id="locale" class="pure-menu-link">Global</a>
      <ul class="pure-menu-children">
        <li class="pure-menu-item"><a onclick="MDB.render('Global')" class="pure-menu-link">Global</a></li>
        <li class="pure-menu-item"><a onclick="MDB.render('English')" class="pure-menu-link">English</a></li>
        <li class="pure-menu-item"><a onclick="MDB.render('繁體中文')" class="pure-menu-link">繁體中文</a></li>
        <li class="pure-menu-item"><a onclick="MDB.render('简体中文')" class="pure-menu-link">简体中文</a></li>
      </ul>
    </li>
  </ul>
</div>

<div id="layout">
  <a href="#menu" id="menuLink" class="menu-link"><span></span></a>
  <div id="menu">
    <div id="sideMenu" class="pure-menu">
      <div clas
packetLen=1460
----------
Response:
----------
s="pure-menu-heading"><a href="/"><i class="fa fa-home" aria-hidden="true" title="Home"></i></a>
        <a href="book.mdo"><i class="fa fa-book" aria-hidden="true" title="Book"></i></a>
        <a href="../../view//"><i class="fa fa-user" aria-hidden="true" title="Author"></i></a>
      </div>
      <ul class="pure-menu-list" id="bookBox">
      </ul>
    </div>
  </div>
  <div id="main">
    <div class="content" id="viewBox" hidden>
      <div id="mdBox"></div>
      <div style="text-align:center">
        <span class="footnote">
        <label class="mt" data-mt="Author=作者">Author</label> ： <a href="/view/ccc/">ccc</a> ,
        <label class="mt" data-mt="Licensed in=使用請遵循">Licensed in</label> <a href="../../view/license/notSpecified.md" class="mt" data-mt="License=授權聲明">授權聲明</a>
<!--     ,    <label class="mt" data-mt="Welcome to=歡迎"></label> <a href="#sms" class="mt" data-mt="Comment=評論留言">Comment</a> ！ -->
        </span>
      </div>
    </div>
    <div class="content" id="editBox" hidden>
      <form class="pure-form pure-form-stacked">
      <div style="height:2.5em">
        <button type="button" class="pure-button pure-button-primary mt" data-mt="Save=儲存" onclick="MDB.save()">Save</button>
        <select id="watchOption" style="float:right">
          <option value="no"  class="mt" data-mt="No Translation=不翻譯" selected="selected"> 不翻譯 </option>
          <option
packetLen=1460
----------
Response:
----------
 value="c2e" class="mt" data-mt="Chinese to English=中翻英"> 中翻英 </option>
          <option value="e2c" class="mt" data-mt="English to Chinese=英翻中"> 英翻中 </option>
        </select>
      </div>
      </form>
      <div id="watch" style="height:5em" hidden></div>
      <textarea id="editText" name="editText"># 陳鍾誠

欄位          | 內容
--------------|------------------------------------------------------------
[履歷](https://www.cakeresume.com/f5611f)  | to [學生](cccForStudent.md) , [程式人](cccForProgrammer.md) , [教授](cccForProfessor.md) , [公司](cccForCompany.md)
職務      | [金門大學](http://www.nqu.edu.tw/) / [資訊工程](http://www.nqu.edu.tw/educsie/index.php) / [教師](http://www.nqu.edu.tw/educsie/index.php?act=blog&code=list&ids=4)
專長          | 寫程式 ( [NodeJS](https://nodejs.org/) + [JavaScript](js1.md) + [C](c1.md) ) , 寫書 ( [Markdown](https://zh.wikipedia.org/wiki/Markdown) )
聯絡          | ccckmit@gmail.com , [Facebook](https://www.facebook.com/ccckmit)
帳號          | [Github](https://github.com/ccckmit) , [SlideShare](http://www.slideshare.net/ccckmit/) , [YouTube](https://www.youtube.com/user/ccckmit)
作品          | [課程](course.md) , [書籍](booklist.md) , [程式](codelist.md) , [小說](novel.md) , [散文](article.md)  , [詩](../poem/) , [十 分鐘系列](../slide/)
研究          | [聊天機器人](../bot/) , [機器翻譯](../mt/) , [
packetLen=1760
----------
Response:
----------
人造語](../artilang/) , [Markdown 物件格式應用](../mdo/)
關注          | [軟體工具](tool.md) , [研究主題](topic.md) , [程式語言](language.md) , [圖靈獎](turingAward.md)



</textarea>
      <textarea id="editBook" name="editBook" style="display:none">{
 "title": "Home of C.C.Chen=陳鍾誠的網站",
 "editor": "ccc",
 "locale": "繁體中文",
 "chapters": [
  {
   "title": "C.C.Chen=陳鍾誠",
   "link": "README.md"
  },
  {
   "title": "Course=課程地圖",
   "link": "course.md"
  },
  {
   "title": "Book=書籍著作",
   "link": "booklist.md"
  },
  {
   "title": "Code=程式作品",
   "link": "codelist.md"
  },
  {
   "title": "Novel=小說故事",
   "link": "novel.md"
  },
  {
   "title": "Article=散文記事",
   "link": "article.md"
  },
  {
   "title": "Paper=論文研究",
   "link": "paper.md"
  },
  {
   "title": "Slide=十分鐘系列",
   "link": "../slide/"
  },
  {
   "title": "License=授權聲明",
   "link": "license.md"
  }
 ],
 "book": "ccc"
}</textarea>
    </div>
    <div class="content" id="pluginBox" hidden></div>
  </div>
</div>
<script src="../../f6.js"></script>
<script src="../../mdbook.js"></script>
<script>
MDB.setting = {
  user: '',
  book: 'ccc',
  file: 'README.md',
  locale: '繁體中文',
  showdownJsUrl: 'https://cdnjs.cloudflare.com/ajax/libs/showdown/1.6.0/showdown.min.js',
  highlightCssUrl: 'https://cdnjs.cloudflare.com/ajax/libs/highlight.js/9.9.0/styles/default.min.css',
  katexCssUrl: 'https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.7.1/katex.min.css',
  katexJsUrl: 'https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.7.1/katex.min.js',
  highlightJsUrl: 'https://cdnjs.cloudflare.com/ajax/libs/highlight.js/9.9.0/highlight.min.js',
}
</script>
</body>
</html>

packetLen=0
No more message!


```

