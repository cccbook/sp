var fs = require("fs");
var c  = console;
var file = process.argv[2];

vm2asm(file+".vm", file+".asm");

var staticBegin = 16;
var ws;

function vm2asm(vmFile, asmFile) {
  var vmText = fs.readFileSync(vmFile, "utf8"); // 讀取檔案到 text 字串中
  ws = fs.createWriteStream(asmFile);
  var lines   = vmText.split(/\r?\n/); // 將組合語言分割成一行一行
  c.log(JSON.stringify(lines, null, 2));
  pass1(lines);
} 

function parse(line, i) {
  line.match(/^([^\/]*)(\/.*)?$/);
  line = RegExp.$1.trim();
  if (line.length===0)
    return null;
	var tokens = line.split(/\s/);
	return { op: tokens[0], tokens:tokens };
}

function translate(p, ws) {
  var type = p.tokens[1];
	var arg  = p.tokens[2];
	switch (p.op) {
		case "push": push(type, arg); break;
		case "pop":
		case "add":  binary("D+A"); break;
	}
}

function push(type, arg) {
  if (type === "constant")
	 	valToStack(arg);
	else if (type == "static")
		staticToStack(arg);
}

function pop(arg) {
	if (pType == "static")
		stackToStatic(arg);
}

function valToStack(val) { // *SP = val
	A(val);
	C("D=A");
	compToStack("D");
}

/* 
static: mapped on RAM[16 ... 255];
each segment reference static i appearing in a
VM file named f is compiled to the assembly
language symbol f.i (recall that the assembler further
maps such symbols to the RAM, from address 16 onward)*/

function staticToStack(i) { // *SP = val
  A(staticName(i));    // A=file.#
	C("D=M");            // D=file.#
	compToStack("D");
}

function staticName(i) {
	return file+"."+i;
}

function stackToStatic(i) {
	stackToDest('D');
	A(staticName(i));
	C('M=D');
}

function binary(comp) {
	decSp();           // --SP
	stackToDest('D');  // D=*SP
	decSp();           // --SP
	stackToDest('A');	 // A=*SP
	C('D='+comp);      // D=comp
	compToStack('D');  // *SP=D
	incSp();
}

function A(address) {  // A command : @address
	var command = "@"+address;
	c.log(command);
  ws.write(command+"\n");
}

function C(command) {  // C command : Dest=Comp; Jump
	c.log(command);
	ws.write(command+"\n");
}

function stackToDest(dest) {
  loadSp();
  C(dest+'=M');   // dest=*SP
}

function loadSp() {
  A('SP');  // A=&SP
  C('A=M'); // A=M[&SP]=SP
}

function compToStack(comp) { // *SP=comp
	loadSp();
	C('M='+comp);
}

function incSp() { // *SP++
	A("SP");
	C("M=M+1");
}

function decSp() { // *SP--
	A("SP");
	C("M=M-1");
}

function init() { // SP = 256
  comment("init");
	A("SP");
	C("M=256");
}

function comment(msg) {
	c.log("// "+msg);
  ws.write("// "+msg+"\n");
}

function pass1(lines, asmFile) {
  c.log("============== pass1 ================");
	init();
  for (var i=0; i<lines.length; i++) {
    var p = parse(lines[i], i);
    if (p===null) continue;
    comment(lines[i]);
		translate(p);
  }
	ws.end();
}
