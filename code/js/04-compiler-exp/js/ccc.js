var util = require("util");
var assert = require("assert");
var fs = require("fs");

var c = {};                 // 本模組的傳回物件
c.log = console.log;        // 將 console.log 名稱縮短一點
c.format = util.format;     // 字串格式化
c.assert = assert.ok;       // assert 函數，若不符合條件則程式會停止
c.bits = function(word, from, to) { return word << (31-to) >>> (31-to+from); }      // 取得 from 到 to 之間的位元
c.signbits = function(word, from, to) { return word << (31-to) >> (31-to+from); }   // 取得 from 到 to 之間的位元
c.nonull = function(o) { if (o == null) return ""; else return o; }                 // 將 null 改為空字串傳回

c.space = "                                                                      "; // 空白字串，dup() 函數中使用到的。
c.dup = function(ch, n) {           // 傳回 ch 重複 n 次的字串；範例：dup('x', 3) = 'xxx'
  assert.ok(n < c.space.length);
  return c.space.substr(0, n).replace(/ /g, ch); 
}

c.fill = function(ch, o, len) {     // 將字串填滿 ch，例如：fill(' ', 35, 5) = '35   '; fill('0', 35, -5) = '00035';
  var str = o.toString();
  if (len >= 0)
    return str+c.dup(ch, len-str.length);
  else
    return c.dup(ch, -len-str.length)+str;
}

c.base = function(n, b, len) {      // 將數字 n 轉換為以 b 為基底的字串；例如：base(31, 16, 5) = '0001F';
  var str = n.toString(b);
  return c.dup('0', len-str.length)+str;
}

c.hex = function(n, len) {          // 將數字 n 轉換 16 進位；例如：hex(31, 5) = '0001F'; hex(-3, 5) = 'FFFFD'
  var str = (n < 0 ? (0xFFFFFFFF + n + 1) : n).toString(16).toUpperCase();
  if (n < 0)
    return c.fill('F', str, -len).substr(-len);
  else
    return c.fill('0', str, -len).substr(-len);
}

c.str2hex = function(str) {         // 將字串轉為 16 進位碼，例如：str2hex('Hello!') = '48656C6C6F21'
  var hex="";
  for (i=0; i<str.length; i++) {
    var code = str.charCodeAt(i);
    hex += c.hex(code, 2);
  }
  return hex;
}

c.error = function(msg, err) {
   c.log(msg);
   c.log("Error : (%s):%s", err.name, err.message);
   c.log(err.stack);
   process.exit(1);
}

c.printf = function() {
  return process.stdout.write(util.format.apply(null, arguments)); 
}

c.test = function() {
  c.log("bits(0xF3A4, 4, 7)=%s", c.hex(c.bits(0xF3A4, 4, 7), 4));
  c.log("dup('x', 3)=%s", c.dup('x', 3));
  c.log("fill('0', 35, -5)=%s", c.fill('0', 35, -5));
  c.log("base(100, 16, 5)=%s", c.base(100, 16, 5));
  c.log("hex(-100)=%s", c.hex(-100, 6));
  c.log("str2hex(Hello!)=%s", c.str2hex("Hello!"));
}

if (process.argv[2] == "-d")
    c.test();

module.exports = c;
