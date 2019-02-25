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

var R_SP=0, R_LCL=1, R_ARG=2,	R_THIS=3, R_THAT=4, R_TEMP=5, R_FRAME=13, R_RET=14, R_COPY=15, labelTop=0;
var memType = { local:{label:'LCL' }, argument:{label:'ARG' }, 'this':{label:'THIS' }, that:{label:'THAT' }};	
var regType = { reg:{base:0 }, pointer:{base:3}, temp:{base:5} };

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
  var p1 = p.tokens[1];
  var p2 = p.tokens[2];
  switch (p.op) {
    case "push": cmdPush(p1, p2); break;
    case "pop":  cmdPop(p1, p2); break;
    case "add":  cmdBinary("D+A"); break;
    case "sub":  cmdBinary("A-D"); break;
    case "and":  cmdBinary("D&A"); break;
    case "or" :  cmdBinary("D|A"); break;
    case "not":  cmdUnary("!D"); break;
    case "neg":  cmdUnary("-D"); break;
    case "eq" :  cmdCompare("JEQ"); break;
    case "gt" :  cmdCompare("JGT"); break;
    case "lt" :  cmdCompare("JLT"); break;
    case "goto": cmdGoto(p1);
    case "if-goto": cmdIfGoto(p1); break;
    case "label": cmdLabel(p1); break;
    case "function": cmdFunction(p1, parseInt(p2)); break;
    case "call"  : cmdCall(p1, parseInt(p2));
    case "return": cmdReturn(); break;
    default: error();
  }
}

function cmdFunction(name, n) {
  cmdLabel(name);
  for (var i=0; i<n; i++) {
    cmdPush("constant", 0);
  }
}

function cmdCall(name, n) {
  var returnAddress = newLabel();
  cmdPush("constant", returnAddress); // push return_address
  cmdPush("reg", R_LCL);              // push LCL
  cmdPush("reg", R_ARG);              // push ARG
  cmdPush("reg", R_THIS);             // push THIS
  cmdPush("reg", R_THAT);             // push THAT
  loadSeg("R"+R_SP, -n-5);
  compToReg(R_ARG, 'D');              // ARG=SP-n-5
  regToReg(R_LCL, R_SP);              // LCL=SP
  A(name);                            // A=function_name
  C('0; JMP');                        // 0;JMP
  cmdLabel(returnAddress);            // (return_address)
}

function regToReg(dest, src) {
  regToDest('D', src);
  compToReg(dest, 'D');        // Rdest = Rsrc
}

function prevFrameToReg(reg) {
  regToDest('D', R_FRAME);     // D=FRAME
  C('D=D-1');                  // D=FRAME-1
  compToReg(R_FRAME, 'D');     // FRAME=FRAME-1
  C('A=D');                    // A=FRAME-1
  C('D=M');                    // D=*(FRAME-1)
  compToReg(reg, 'D');         // reg=D
}

function cmdReturn() {
  regToReg(R_FRAME, R_LCL);   // R_FRAME = R_LCL
  A("5");                     // A=5
  C("A=D-A");                 // A=FRAME-5
  C("D=M");                   // D=M
  compToReg(R_RET, 'D');      // RET=*(FRAME-5)
  cmdPop("argument", 0);      // *ARG=return value
  regToDest('D', R_ARG);      // D=ARG
  compToReg(R_SP, 'D+1');     // SP=ARG+1
  prevFrameToReg(R_THAT);     // THAT=*(FRAME-1)
  prevFrameToReg(R_THIS);     // THIS=*(FRAME-2)
  prevFrameToReg(R_ARG);      // ARG=*(FRAME-3)
  prevFrameToReg(R_LCL);      // LCL=*(FRAME-4)
  prevFrameToReg(R_RET);      // A=RET
  C("0; JMP");                // goto RET
}

function cmdGoto(label) {
  A(label);
  C("0; JMP");
}

function cmdIfGoto(label) {
  popToDest('D');
  A(label);
  C('D; JNE');
}

function popToDest(dest) {
  decSp();
  stackToDest(dest);  // dest=*SP
}

function cmdUnary(comp) {
  decSp();               // --SP
  stackToDest('D');      // D=*SP
  C('D='+comp);          // D=COMP
  compToStack('D');      // *SP=D
  incSp();               // ++SP
}

function cmdCompare(j) {
  decSp();               // --SP
  stackToDest('D');      // D=*SP
  decSp();               // --SP
  stackToDest('A');      // A=*SP
  C('D=A-D');            // D=A-D
  var label_eq = jump('D', j);  // D;jump to label_eq
  compToStack('0');      // *SP=0
  var label_ne = jump('0', 'JMP'); // 0;JMP to label_ne
  cmdLabel(label_eq);       // (label_eq)
  compToStack('-1');     // *SP=-1
  cmdLabel(label_ne);       // (label_ne)
  incSp();               // ++SP
}

function cmdPush(type, arg) {
  if (type === "constant")
     valToStack(arg);
  else if (type == "static")
    staticToStack(arg);
  else if (type in regType)
    regToStack(type, arg);
  else if (type in memType)
    memToStack(type, arg);
  else
    error();
}

function cmdPop(type, arg) {
  if (type == "static")
    stackToStatic(arg);
  else if (type in regType)
    stackToReg(type, arg);
  else if (type in memType)
    stackToMem(type, arg);
  else
    error();
}

function cmdBinary(comp) {
  decSp();           // --SP
  stackToDest('D');  // D=*SP
  decSp();           // --SP
  stackToDest('A');	 // A=*SP
  C('D='+comp);      // D=comp
  compToStack('D');  // *SP=D
  incSp();
}

function cmdLabel(name) {
  asm("label "+name);
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

function regToStack(seg, i) {
  regToDest('D', regNum(seg, i));    // D=R#
  compToStack('D');                  // *SP=D
}

function regNum(seg, i) {
  return regType[seg].base+i;
}

function stackToReg(seg, i) {
  stackToDest('D', regNum(seg, i));
  compToReg(i, 'D');
}

function compToReg(i, comp) {
  A("R"+i);
  C("M="+comp);
}

function memToStack(seg, i) {
  loadSeg(seg, i, true);
  C('D=M');
  compToStack('D');
}

function stackToMem(seg, i) {
  loadSeg(seg, i, true);
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

function init() {
  comment("init");
  A('256');
  C('D=A');
  compToReg('SP', 'D');    // SP=256
  cmdCall('Sys.init', 0);  // call Sys.init()
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
