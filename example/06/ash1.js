var fs = require("fs");
var c  = console;
var file = process.argv[2];

var dtable = {
  ""   :0b000,
  "M"  :0b001,
  "D"  :0b010,
  "MD" :0b011,
  "A"  :0b100,
  "AM" :0b101,
  "AD" :0b110,
  "AMD":0b111
}

var jtable = {
  ""   :0b000,
  "JGT":0b001,
  "JEQ":0b010,
  "JGE":0b011,
  "JLT":0b100,
  "JNE":0b101,
  "JLE":0b110,
  "JMP":0b111
}

var ctable = {
  "0"   :0b0101010,
  "1"   :0b0111111,
  "-1"  :0b0111010,
  "D"   :0b0001100,
  "A"   :0b0110000, 
  "M"   :0b1110000,
  "!D"  :0b0001101,
  "!A"  :0b0110001, 
  "!M"  :0b1110001,
  "-D"  :0b0001111,
  "-A"  :0b0110011,
  "-M"  :0b1110011,
  "D+1" :0b0011111,
  "A+1" :0b0110111,
  "M+1" :0b1110111,
  "D-1" :0b0001110,
  "A-1" :0b0110010,
  "M-1" :0b1110010,
  "D+A" :0b0000010,
  "D+M" :0b1000010,
  "D-A" :0b0010011,
  "D-M" :0b1010011,
  "A-D" :0b0000111,
  "M-D" :0b0000111,
  "D&A" :0b0000000,
  "D&M" :0b1000000,
  "D|A" :0b0010101,
  "D|M" :0b1010101
}


assemble(file+'.asm', file+'.hack');

function assemble(asmFile, objFile) {
  var asmText = fs.readFileSync(asmFile, "utf8"); // 讀取檔案到 text 字串中
  var lines   = asmText.split(/[\r\n]+/); // 將組合語言分割成一行一行
  c.log(JSON.stringify(lines, null, 2));
  pass1(lines);
  pass2(lines, objFile);
} 

function parse(line, i) {
  line = line.replace(/\s/, "");
  if (line.startsWith("//") || line.length===0) 
    return null;
  if (line.startsWith("@")) {
    return { type:"A", address:line.substring(1).trim() }
  } else if (line.match(/^((([AMD]*)=)?([AMD1\+\-\&\|\!]*))(;(\w*))?$/)) {
    return { type:"C", c:RegExp.$4, d:RegExp.$3, j:RegExp.$6 }
  } else {
    throw "Error: line "+(i+1);
  }
}

function pass1(lines) {
  for (var i=0; i<lines.length; i++) {
    var p = parse(lines[i], i);
    if (p===null) continue;
//    c.log("%j", p);
  }
}

function pass2(lines, objFile) {
  var ws = fs.createWriteStream(objFile);
  ws.once('open', function(fd) {
    var address = 0;
    for (var i=0; i<lines.length; i++) {
      var p = parse(lines[i], i);
      if (p===null) continue;
      var code = toCode(p);
      c.log("%s:%s %s", intToStr(i+1, 3, 10), intToStr(code, 16, 2),  lines[i]);
      ws.write(intToStr(code, 16, 2)+"\n");
      address = address + 1;
    }
    ws.end();
  });
}

function intToStr(num, size, radix) {
    var s = num.toString(radix)+"";
    while (s.length < size) s = "0" + s;
    return s;
}

function toCode(p) {
  if (p.type === "A") {
    return parseInt(p.address);
  } else { // if (p.type === "C")
    var d = dtable[p.d];
    var c = ctable[p.c];
    var j = ctable[p.j];
    return 0b111<<13|c<<6|d<<3|j;
  }
}
