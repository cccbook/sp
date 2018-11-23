var opTable = require("./optable");
var opList = [ "LD 00 L", "ST  01 L", "LDB 02 L",  "STB 03 L", "LDR 04 L", 
"STR 05 L", "LBR 06 L",  "SBR 07 L",  "LDI 08 L", "CMP 10 A", "MOV 12 A", 
"ADD 13 A",  "SUB 14 A",  "MUL 15 A", "DIV 16 A",  "AND 18 A", "OR  19 A",  "XOR 1A A",  
"ADDI 1B A", "ROL 1C A",  "ROR 1D A", "SHL 1E A", "SHR 1F A",  
"JEQ 20 J", "JNE 21 J",  "JLT 22 J", "JGT 23 J", "JLE 24 J",  "JGE 25 J", "JMP 26 J", 
"SWI 2A J", "JSUB 2B J","RET 2C J", "PUSH 30 J", "POP 31 J",  "PUSHB 32 J", 
"POPB 33 J", "RESW F0 D", "RESB F1 D", "WORD F2 D", "BYTE F3 D"];

var cpu = { "opTable" : new opTable(opList) };

if (process.argv[2] == "-d")
    cpu.opTable.dump();

module.exports = cpu;
