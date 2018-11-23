var c = require("./ccc"); // 引用基本函式庫 ccc.js
var as = require("./as"); // 引用抽象組譯器物件 as.js
var code = require("./code"); // 引用指令物件 code.js
var cpu0 = require("./cpu0"); // 引用處理器物件 cpu0.js

var as0 = new as(cpu0.opTable); // 建立 as0 組譯器物件

as0.parse = function(line) { // 剖析組合語言指令，建立 code 物件
    return new code(line, this.opTable);
}

as0.translate = function(code) { // 指令的編碼函數
  var ra=0, rb=0, rc=0, cx=0;
  var pc = code.address + 4; // 提取後PC為位址+4
  var args = code.args, parseR = code.parseR; // 取得 code 物件的函數
  var labelCode = null; // JMP label 中 label 所對應行的物件，稱為 labelCode
  if (code.op == undefined) { // 如果沒有指令碼 (只有標記)，則清空目的碼
    code.obj = ""; 
    return;
  }
  switch (code.op.type) { // 根據指令型態
    case 'J' : // 處理 J 型指令，編出目的碼 OP Ra+cx
      switch (code.op.name) {
        case "RET": case "IRET" : // 如果式返回或中斷返回，則只要輸出 op 碼
            break;
        case "SWI" : // 如果是軟體中斷指令，則只有 cx 參數有常數值
            cx = parseInt(args[0]);
            break;
        default : // 其他跳躍指令，例如 JMP label, JLE label 等
            labelCode = this.symTable[args[0]]; // 取得 label 符號位址
            cx = labelCode.address - pc; // 計算 cx 欄位
            break;
      }
      code.obj = c.hex(code.op.id,2)+c.hex(cx, 6); // 編出目的碼 OP Ra+cx
      break;
    case 'L' : // 處理 L 型指令，編出目的碼 OP Ra, Rb, cx
      ra = parseR(args[0]); // 取得 Ra 欄位
      switch (code.op.name) {
        case "LDI" :  // 處理  LDI 指令
            cx = parseInt(args[1]); // 取得 cx 欄位
            break;
        default : // 處理 LD, ST, LDB, STB 指令
            if (args[1].match(/^[a-zA-Z]/)){ // 如果是 LD LABEL 這類情況
              labelCode = this.symTable[args[1]]; // 取得標記的 code 物件
              rb = 15; // R[15] is PC
              cx = labelCode.address - pc; // 計算標記與 PC 之間的差值
            } else { // 否則，若是像 LD Ra, Rb+100 這樣的指令
              rb = parseR(args[2]); // 取得 rb 欄位
              cx = parseInt(args[3]); // 取得 cx 欄位 (例如 100)
            }
            break;
      }
      code.obj = c.hex(code.op.id, 2)+c.hex(ra, 1)+c.hex(rb, 1)+c.hex(cx, 4); // 編出目的碼 OP Ra, Rb, cx
      break;
    case 'A' : // 處理 A 型指令，編出目的碼 OP Ra, Rb, Rc, cx
      ra = parseR(args[0]); // 取得 Ra 欄位
      switch (code.op.name) {
        case "LDR": case "LBR": case "STR": case "SBR":  // 處理  LDR, LBR, STR, SBR 指令，例如 LDR Ra, Rb+Rc
            rb = parseR(args[1]); // 取得 Rb 欄位
            rc = parseR(args[2]); // 取得 Rc 欄位
            break;
        case "CMP": case "MOV" : // 處理 CMP 與 MOV 指令，CMP Ra, Rb; MOV Ra, Rb
            rb = parseR(args[1]); // 取得 Rb
            break;
        case "SHL": case "SHR": case "ADDI": // 處理 SHL, SHR, ADDI 指令，例如 SHL Ra, Rb, Cx
            rb = parseR(args[1]); // 取得 Rb 欄位
            cx = parseInt(args[2]); // 取得 cx 欄位 (例如 3)
            break;
        case "PUSH": case "POP": case "PUSHB": case "POPB" :  // 處理 PUSH, POP, PUSHB, POPB
            break; // 例如 PUSH Ra, 只要處理 Ra 就好，A 型一進入就已經處理 Ra 了。
        default :  // 其他情況，像是 ADD, SUB, MUL, DIV, AND, OR, XOR 等，例如 ADD Ra, Rb, Rc
            rb = parseR(args[1]);  // 取得 Rb 欄位
            rc = parseR(args[2]);  // 取得 Rc 欄位
            break;
      }
      code.obj = c.hex(code.op.id, 2)+c.hex(ra, 1)+c.hex(rb, 1)+c.hex(rc,1)+c.hex(cx, 3); // 編出目的碼 OP Ra, Rb, Rc, cx
      break;
    case 'D' : { // 我們將資料宣告  RESW, RESB, WORD, BYTE 也視為一種指令，其形態為 D
      var unitSize = 1; // 預設的型態為 BYTE，資料大小 = 1
      switch (code.op.name) {                    
        case "RESW":  case "RESB": // 如果是 RESW 或 RESB，例如 a:RESB 2
          code.obj = c.dup('0', this.size(code)*2); // 1 個 byte 的空間要用兩個16進位的 00 去填充
          break;                                    // 例如：a RESB 2 會編為 '0000'
        case "WORD": // 如果是 WORD ，佔 4 個 byte
          unitSize = 4;
        case "BYTE": { // 如果是 BYTE ，佔 1 個 byte
          code.obj = ""; // 一開始目的碼為空的
          for (var i in args) { // 對於每個參數，都要編為目的碼
            if (args[i].match(/^\".*?\"$/)) {  // 該參數為字串，例如： "Hello!" 轉為 68656C6C6F21
              var str = args[i].substring(1, args[i].length-1); // 取得 "..." 中間的字串內容
              code.obj += c.str2hex(str); // 將字串內容 (例如 Hello!) 轉為 16 進位 (例如 68656C6C6F21)
            } else if (args[i].match(/^\d+$/)) {  // 該參數為常數，例如 26
              code.obj += c.hex(parseInt(args[i]), unitSize*2); // 將常數轉為 16 進位目的碼 (例如 26 轉為 1A)
            } else { // 該參數為標記，將標記轉為記憶體位址，例如 msgptr: WORD msg 中的 msg 轉為位址 (例如：00000044)
              labelCode = this.symTable[args[i]]; // 取得符號表內的物件
              code.obj += c.hex(labelCode.address, unitSize*2); // 取得位址並轉為 16 進位，塞入目的碼中。
            }
          }
          break;
        } // case BYTE:
      } // switch
      break;
    } // case 'D'
  }
} 

// 使用範例 node as0 sum.as0 sum.ob0
// 其中 argv[2] 為組合語言檔, argv[3] 為目的檔
as0.assemble(process.argv[2], process.argv[3]); 
