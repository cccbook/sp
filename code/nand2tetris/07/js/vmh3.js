// 本程式主要參考並修改自 https://github.com/havivha/Nand2Tetris

var fs = require("fs");
var c  = console;
var file = process.argv[2];

// SP:R0, LCL:R1, ARG:R2, THIS:R3, THAT:R4, TEMP:R5-12, General Purpose:R13..15
/* 
static: mapped on RAM[16 ... 255];
each segment reference static i appearing in a
VM file named f is compiled to the assembly
language symbol f.i (recall that the assembler further
maps such symbols to the RAM, from address 16 onward)*/

var memType = { local:{label:'LCL'}, argument:{label:'ARG'}, 'this':{label:'THIS'}, that:{label:'THAT'}};
var regType = { reg:{base:0 }, pointer:{base:3}, temp:{base:5} };
var R_COPY = 15, labelTop = 0;

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
		case "pop":  pop(type, arg); break;
		case "add":  binary("D+A"); break;
		case "sub":  binary("A-D"); break;
		case "and":  binary("D&A"); break;
		case "or" :  binary("D|A"); break;
		case "not":  unary("!D"); break;
		case "neg":  unary("-D"); break;
		case "eq" :  compare("JEQ"); break;
		case "gt" :  compare("JGT"); break;
		case "lt" :  compare("JLT"); break;
		default: error();
	}
}

function unary(comp) {
	decSp();               // --SP
	stackToDest('D');      // D=*SP
	C('D='+comp);          // D=COMP
	compToStack('D');      // *SP=D
	incSp();               // ++SP
}

function compare(j) {
	decSp();               // --SP
	stackToDest('D');      // D=*SP
	decSp();               // --SP
	stackToDest('A');      // A=*SP
	C('D=A-D');            // D=A-D
	var label_eq = jump('D', j);  // D;jump to label_eq
	compToStack('0');      // *SP=0
	var label_ne = jump('0', 'JMP'); // 0;JMP to label_ne
	label(label_eq);       // (label_eq)
	compToStack('-1');     // *SP=-1
	label(label_ne);       // (label_ne)
	incSp();               // ++SP
}

function jump(comp, j) {
	var label = newLabel();
//	c.log(" ==> label="+label+" labelTop="+labelTop);
	A(label);
	C(""+comp+";"+j);
	return label;
}

function newLabel() {
  labelTop++;
  return "LABEL"+labelTop;
}

function error() {
	throw "Error:";
}

function push(type, arg) {
  if (type === "constant")
	 	valToStack(arg);
	else if (type == "static")
		staticToStack(arg);
	else if (typeof regType[type] !== 'undefined')
		regToStack(arg);
	else if (typeof memType[type] !== 'undefined')
		memToStack(arg);
	else
		error();
}

function pop(type, arg) {
	if (type == "static")
		stackToStatic(arg);
	else if (typeof regType[type] !== 'undefined')
		stackToMem(arg);
	else if (typeof memType[type] !== 'undefined')
		stackToReg(arg);
	else
		error();
}

function valToStack(val) { // *SP = val
	A(val);
	C("D=A");
	compToStack("D");
}

function staticToStack(i) { // *SP = val
  A(staticName(i));    // A=file.#
	C("D=M");            // D=file.#
	compToStack("D");
}

function stackToStatic(i) {
	stackToDest('D');
	A(staticName(i));
	C('M=D');
}

function regToStack(i) {
	regToDest('D', i);    // D=R#
  compToStack('D');  // *SP=D
}

function stackToReg(i) {
	stackToDest('D');
	compToReg(i, 'D');
}

function compToReg(i, comp) {
	A("R"+i);
	C("M="+comp);
}

function memToStack(i) {
  loadSeg(i, true);
	C('D=M');
	compToStack('D');
}

function stackToMem(i) {
	loadSeg(i, true);
	compToReg(R_COPY, 'D');      // R_COPY=D
	stackToDest('D');            // D=*SP
	regToDest('A', R_COPY);      // A=R_COPY
	C('M=D');           				 // *(seg+index)=D
}

function loadSeg(seg, i, indir) {
	if (i===0)
		loadSegNoIndex(seg, indir);
	else
		loadSegIndex(seg, i, indir);
}

function loadSegNoIndex(seg, indir) {
	A(seg);
	if (indir) C('AD=M');
}

function loadSegIndex(seg, i, indir) {
	A(Math.abs(i)+'');     					// A=index
	C('D=A');     				// D=A
	A(seg);     					// A=seg
	if (indir) C('A=M');  // A=*seg
	if (i>=0)
		C('AD=D+A')
	else
		C('AD=A-D');     		// A=D=seg+/-index
}

function regToDest(dest, i) {
  A("R"+i);     // @R#
	C(dest+"=M"); // dest=R#
}

function staticName(i) {
	return file+"."+i;
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

function asm(line) {
	c.log(line);
	ws.write(line+"\n");
}

function A(address) {  // A command : @address
	asm("@"+address);
}

function C(command) {  // C command : Dest=Comp; Jump
  asm(command);
}

function label(name) {
	asm("label "+name);
}

function comment(msg) {
	asm("// "+msg);
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
