// ir2as0 中間碼轉換為組合語言，用法範例： node ir2as0 test.ir0 > test.as0
var fs = require("fs");
var util = require("util");
var format = util.format;  // 字串格式化
var log = console.log;     // 將 console.log 名稱縮短一點

// 讀入中間檔，並分割成一行一行的字串
var lines = fs.readFileSync(process.argv[2], "utf8").split("\n"); 

// 輸出組合語言
var asm=function(label, op, p, p1, p2) {
  var asCode = format("%s\t%s\t%s\t%s\t%s", label, op, p, p1, p2);
  log(asCode);
}

var cmpCount = 0; // 比較運算的標記不可重複，故加上一個 counter 以玆區分

// 將一行中間碼 line 轉換為組合語言
function ir2as(line) {
  var tokens = line.split("\t"); // 將中間碼分割成一個一個的欄位
  var label = tokens[0];         // 取出標記 label
  var iop = tokens[1], aop="";   // 取出運算 iop
  var p = tokens.slice(2);       // 取出參數部份
  if (label !== "")              // 若有標記，直接輸出一行只含標記的組合語言
    asm(label, "", "", "", "");
  switch (iop) {                 // 根據運算 iop 的內容，決定要轉成甚麼組合語言
    case "=":                    // 範例：= X Y 改為 LD R1, Y; ST R1, X
	asm("", "LD", "R1", p[1], "");
	asm("", "ST", "R1", p[0], "");
	break;
    // 範例： + X A B 改為 LD R1, A;  LD R2, B; ADD R3, R1, R2; ST R3, X;
    case "+": case "-": case "*": case "/": case "<<":
	asm("", "LD", "R1", p[1], "");
	asm("", "LD", "R2", p[2], "");
	aop = {"+":"ADD", "-":"SUB", "*":"MUL", "/":"DIV"}[iop];
	asm("", aop, "R3", "R1", "R2");
	asm("", "ST", "R3", p[0], "");
	break;
    // 範例： ++ X 改為 LDI R1, 1; LD R2, X; ADD R2, R1, R2; ST R2, X; 
    case "++": case "--":
	asm("", "LDI", "R1", "1", "");
	asm("", "LD",  "R2", p[0], "");
	aop = {"++":"ADD", "--":"SUB" }[iop];
	asm("", aop, "R2", "R1", "R2");
	asm("", "ST",  "R2", p[0]);
	break;
    // 範例： < X, A, B 改為 LD R1, A; LD R2, B; CMP R1, R2; JLT CSET0; LDI R1, 1; JMP EXIT0; CSET0: LDI R1, 0; CEXIT0: ST R1, X
    case "<": case "<=": case ">": case ">=": case "==": case "!=": 
	asm("", "LD", "R1", p[1], "");
	asm("", "LD", "R2", p[2], "");
	asm("", "CMP", "R1", "R2", "");
	aop = {"<":"JLT", "<=":"JLE", ">":"JGT", ">=":"JGE", "==":"JEQ", "!=":"JNE"}[iop];
	asm("", aop, "CSET"+cmpCount, "", "");
	asm("", "LDI", "R1", "1", "");
	asm("",  "JMP", "CEXIT"+cmpCount, "", "");
	asm("CSET"+cmpCount, "LDI", "R1", "0", "");
	asm("CEXIT"+cmpCount, "ST", "R1", p[0], "");
	break;
    // 範例： call X, F 改為 CALL F; ST R1, X;
    case "call":
	asm("",  "CALL", p[1], "",   "");
	asm("",  "ST",   "R1", p[0], "");
	break;
    // 範例： arg X 改為 LD R1, X; PUSH R1;
    case "arg":
	asm("",  "LD",  "R1", p[0], "");
	asm("",  "PUSH","R1", "", "");
	break;
    case "function": // 範例： sum function 只生成標記 sum，沒有生成組合語言指令
	break;
    case "endf": // 函數結束，沒有生成組合語言指令
	break;
    case "param": // 範例： param X 改為 POP R1; ST R1, X; 
	asm("",  "POP", "R1", "", "");
	asm("",  "ST",  "R1", p[0], "");
	break;
    case "return":  // 範例： return X 改為 LD R1, X; RET;
	asm("",  "LD","R1", p[0], "");
	asm("",  "RET","", "", "");
	break;
    case "if0":  // 範例： if0 X Label 改為 CMP R0, X; JEQ Label;
	asm("",  "CMP","R0", p[0], "");
	asm("",  "JEQ",p[1], "", "");
	break;
    case "goto":  // 範例： goto Label 改為 JMP label
	asm("",  "JMP", p[0], "", "");
	break;
    case "array":  // 範例： X array 改為 LD R1, X; CALL ARRAY; (註： X=new array())
	asm("",  "LD", "R1", p[0], "");
	asm("",  "CALL", "ARRAY", "", "");
	break;
    case "[]":  // 範例： [] X A i  改為 LD R1, A; LD R2, i; CALL AGET; ST R1, X (註： X=A[i])
	asm("",  "LD", "R1", p[1], "");
	asm("",  "LD", "R2", p[2], "");
	asm("",  "CALL", "AGET", "", "");
	asm("",  "ST", "R1", p[0], "");
	break;
    case "length": // 範例： length len, A 改為 LD R1, A; CALL ALEN; ST R1, len;
	asm("",  "LD", "R1", p[1], "");
	asm("",  "CALL", "ALEN", "", "");
	asm("",  "ST", "R1", p[0], "");
	break;
    case "apush": // 範例： apush A, X 改為 LD R1,A; LD R2, X; CALL APUSH
	asm("",  "LD", "R1", p[0], "");
	asm("",  "LD", "R2", p[1], "");
	asm("",  "CALL", "APUSH", "", "");
	break;
    case "table": // 範例： table T 改為 LD R1,T; CALL TABLE
	asm("",  "LD", "R1", p[0], "");
	asm("",  "CALL", "TABLE", "", "");
	break;
    case "map": // 範例： map table field value 改為 LD R1, table; LD R2, field; LD R3, value; CALL TMAP
	asm("",  "LD", "R1", p[0], "");
	asm("",  "LD", "R2", p[1], "");
	asm("",  "LD", "R3", p[2], "");
	asm("",  "CALL", "TMAP", "", "");
	break;
    case "":
	break;
    default: 
      log("Error : %s not found!", iop);
  }
}

// 將所有中間碼都轉換為組合語言
for (var i in lines) {
  if (lines[i].trim().length > 0) {
    log("// %s", lines[i]);
    ir2as(lines[i]);
  }
}