var c = require("./ccc");
var as = require("./as");
var code = require("./code");
var cpu1 = require("./cpu1");

var as1 = new as(cpu1.opTable);

as1.parse = function(line) {
  return new code(line, this.opTable);
}

as1.translate = function(code) { // 指令的編碼函數
  var ra=0, rb=0, rc=0, cx=0;
  var pc = code.address + 4;                     // 提取後PC為位址+4
  var args = code.args, parseR = code.parseR;
  var labelCode = null;
  switch (code.op.type) {
    case "N": 
        code.obj = c.hex(code.op.id, 2) + c.hex(0, 6); 
        break;
    case "C":
        ra = parseR(args[0]);
        rb = parseR(args[1]);
        cx = parseInt(args[2]);
        code.obj = c.hex(code.op.id, 2)+c.hex(ra, 1)+c.hex(rb, 1)+c.hex(cx, 4);
        break;
    case "L":
        ra = parseR(args[0]);
        rb = 15;
        labelCode = this.symTable[args[1]];
        cx = labelCode.address - pc;
        code.obj = c.hex(code.op.id, 2)+c.hex(ra, 1)+c.hex(rb, 1)+c.hex(cx, 4);
        break;
    case "D":
      var unitSize = 1;
      switch (code.op.name) {
        case "RESW":                             // 如果是 RESW
        case "RESB":                             //     或 RESB
          code.obj = c.dup('0', code.size()*2);
          break;                            
        case "WORD":                             // 如果是 WORD:
          unitSize = 4;
        case "BYTE": {                           // 如果是 BYTE : 輸出格式為 %2x
          code.obj = "";
          for (var i in args) {
            if (args[i].match(/\d+/))            // 常數
              code.obj += c.hex(parseInt(args[i]), unitSize*2);
            else {                               // 標記
              labelCode = symTable[args[i]];
              code.obj += c.hex(labelCode.address, unitSize*2);
            }
          }
          break;
        } // case BYTE: 
      } // switch 
  } // case "D"
}

as1.assemble(process.argv[2], process.argv[3]);
