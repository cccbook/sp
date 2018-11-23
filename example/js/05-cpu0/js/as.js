var fs = require("fs"); // 引用檔案函式庫
var c = require("./ccc"); // 引用基本函式庫 ccc.js
var Memory = require("./memory"); // 引用記憶體物件 memory.js

var as = function(opTable) { // 抽象組譯器物件
 this.opTable = opTable; // 取得指令表 opTable

 this.assemble = function(asmFile, objFile) { // 組譯器的主要函數
  this.lines = []; this.codes = []; // 設定程式碼行 (lines)，指令陣列 (codes)
  this.symTable = {}; // 建立空的符號表 (symTable)
  c.log("Assembler:asmFile=%s objFile=%s", asmFile, objFile); // 輸入組合語言、輸出目的檔
  c.log("===============Assemble=============");
  var text = fs.readFileSync(asmFile, "utf8"); // 讀取檔案到 text 字串中
  this.lines = text.split(/[\r\n]+/); // 將組合語言分割成一行一行
  c.log(this.lines); // 印出組合語言以便觀察
  this.pass1(); // 第一階段：計算位址
  c.log("===============SYMBOL TABLE=========");
  for (s in this.symTable) { // 印出符號表以便觀察
    c.log("%s %s", c.fill(' ',s,8), c.hex(this.symTable[s].address, 4));
  }
  this.pass2(); // 第二階段：建構目的碼
  this.saveObjFile(objFile); // 輸出目的檔
 }

 this.pass1 = function() { // 第一階段的組譯
  var address = 0;  // 程式計數器 PC 的起始位址為 0
  c.log("=================PASS1================");
  for (var i in this.lines) { // 對於每一行
    try {
      var code = this.parse(this.lines[i]); // 剖析並建立 code 物件
      code.address = address; // 設定該行的位址
      if (code.label.length != 0) { // 如果有標記符號
        this.symTable[code.label] = code; // 加入符號表中
      }
      this.codes.push(code); // 將剖析完成的指令放入陣列中
      c.log("%s", code); // 印出指令物件
      address += this.size(code); //  計算下一個指令位址
    } catch (err) { // 語法有錯，印出錯誤的行號與內容
      c.error(c.format("line %d : %s", i, this.lines[i]), err);
    }
  }
 }

 this.pass2 = function(codes) { // 組譯器的第二階段
  c.log("=============PASS2==============");
  for (var i in this.codes) { // 對每一個指令
    try {
      this.translate(this.codes[i]); // 將組合語言指令翻譯成機器碼
      c.log("%s", this.codes[i]); // 印出指令物件 (含組合語言與機器碼)
    } catch (err) { // 語法有錯，印出錯誤的行號與內容
      c.error(c.format("line %d : %s", i, this.lines[i]), err);
    }
  }
 }
 
 this.saveObjFile = function(objFile) { // 儲存目的檔
  c.log("=================SAVE OBJ FILE================");
  var obj = ""; // obj 為目的檔的 16 進位字串，初始化為空字串
  for (var i in this.codes) // 對於每個指令
    obj += this.codes[i].obj; // 都將目的碼加入 obj 字串中。
  var m = new Memory(1); // Memory 物件，用來將 16 進位目的碼轉為 2 進位儲存。
  m.loadhex(obj); // 將 16 進位目的碼載入記憶體
  m.dump(); // 輸出記憶體內容
  m.save(objFile); // 將記憶體內容除存到目的檔 objFile 中。
 }

 this.size = function(code) { // 計算指令所佔空間大小，在 pass1() 當中會呼叫此函數
    var len = 0, unitSize = 1; // len: 指令大小 , unitSize:每單位大小 (BYTE=1, WORD=4)
    switch (code.op.name) { // 根據運算碼 op
      case "RESW" : return 4 * parseInt(code.args[0]);  // 如果是 RESW, 大小為 4*保留量(參數 0)
      case "RESB" : return 1 * parseInt(code.args[0]);  // 如果是 RESB, 大小為 1*保留量(參數 0)
      case "WORD" : unitSize = 4; // 沒有 break，繼續執行到 BYTE 部分的程式 (共用)
      case "BYTE" : // 如果是BYTE, 大小是 1*參數個數 
        for (i in code.args) { // 對於 BYTE 或 WORD 中的每個元素
          if (code.args[i].match(/^\".*?\"$/)) // 如果是字串，像 "Hello!"
            len += (code.args[i].length - 2) * unitSize; // 則大小為 unitSize*字串長度
          else // 否則 大小就是 unitSize (BYTE=1, WORD=4)
            len += unitSize;
        }
        return len;
      case "" : return 0; // 如果只是標記, 大小為 0
      default : return 4; // 其他情形 (指令), 大小為 4
    }
 }  
}

module.exports = as; // 匯出「抽象組譯器物件 as 」