var fs = require("fs");
var c  = console;
var file = process.argv[2];

vm2asm(file+".vm", file+".asm");

var ws;

function vm2asm(vmFile, asmFile) {
  var vmText = fs.readFileSync(vmFile, "utf8"); // 讀取檔案到 text 字串中
  ws = fs.createWriteStream(asmFile);
  var lines   = vmText.split(/\r?\n/); // 將組合語言分割成一行一行
  c.log(JSON.stringify(lines, null, 2));
  pass1(lines);
} 

function parse(line, i) {
  if (line.length===0)
    return null;
	var tokens = line.split(/\s/);
	return { op: tokens[0], tokens:tokens };
}

function translate(p, ws) {
	switch (p.op) {
		case "push":
		  var pType = p.tokens[1];
			var pArg  = p.tokens[2];
			if (pArg.match(/\d+/)) {
				A(pArg);
				C("D=A");
				compToStack('D');
			}
			break;
		case "add":
		  binary("D+A");
			break;
	}
}

function binary(comp) {
	decSp();                     // --SP
	stackToDest('D');            // D=*SP
	decSp();                     // --SP
	stackToDest('A');						 // A=*SP
	C('D='+comp);                // D=comp
	compToStack('D');            // *SP=D
	incSp();
}

function A(address) {
	var command = "@"+address;
	c.log(command);
  ws.write(command+"\n");
}

function C(command) {
	c.log(command);
	ws.write(command+"\n");
}

function stackToDest(dest) {
  loadSp();
  C(dest+'=M');   // dest=*SP
}

function loadSp() {
  A('SP');
  C('A=M');
}

function compToStack(comp) {
	loadSp();
	C('M='+comp);
}

function valToStack(val) {
	A(val);
	C("D=A");
	compToStack("D");
}

function incSp() {
	A("SP");
	C("M=M+1");
}

function decSp() {
	A("SP");
	C("M=M-1");
}

function init(ws) {
	A("SP");
	C("M=256");
}

function pass1(lines, asmFile) {
  c.log("============== pass1 ================");
	init(ws);
  for (var i=0; i<lines.length; i++) {
    var p = parse(lines[i], i);
		if (p===null) continue;
		C("//" + lines[i] + "\n");
		translate(p, ws);
  }
	ws.end();
}
