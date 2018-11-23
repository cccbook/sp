var opTable = require("./optable");
var opList = ["LD   00 L", "ST   01 L",  "LDB  02 L", "STB   03 L", 
"ADDI 12 C",  "ADD  13 L", "SUB  14 L",  "MUL  15 L", "DIV   16 L", "AND  18 L", 
"OR   19 L",  "XOR  1A L", "ROL  1C L",  "ROR  1D L", "SHL   1E L", "SHR  1F L",  
"JZ   20 L",  "RET  2C N", "PUSH 30 L",  "POP  31 L", "PUSHB 32 L", "POPB 33 L", 
"RESW F0 D",  "RESB F1 D", "WORD F2 D",  "BYTE F3 D"];

var cpu = { "opTable" : new opTable(opList) };
// cpu.opTable.dump();
module.exports = cpu;
