var c = require("./ccc");
var cpu1 = require("./cpu1");
var Memory = require("./memory");

var IR = 16, PC = 15, LR = 14, SP = 13, SW = 12;
var ID = function(op) { return cpu1.opTable[op].id; }

var run = function(objFile) {
    R = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 13, 14, 0, 16];
    m = new Memory(1);
    m.load(objFile);
    var stop = false;
    while (!stop) {                                          // 如果尚未結束
      var tpc = R[PC];
      R[0] = 0;                                              // R[0] 永遠為 0
      R[IR] = m.geti(R[PC]);                                 // 指令擷取，IR=[PC..PC+3]
      R[PC] += 4;                                            // 擷取完將 PC 加 4，指向下一個指令
      var op = c.bits(R[IR], 24, 31);                                 // 取得 op 欄位，IR[24..31]
      var ra = c.bits(R[IR], 20, 23);                                 // 取得 ra 欄位，IR[20..23]
      var rb = c.bits(R[IR], 16, 19);                                 // 取得 rb 欄位，IR[16..19]
      var c16= c.signbits(R[IR], 0,  15);                             // 取得 16 位元的 cx
      var c5 = c.bits(R[IR], 0,   4);
      var addr = R[rb]+c16;
      switch (op) {                                            // 根據op執行動作
        case ID("LD") : R[ra] = m.geti(addr); break;        // 處理 LD 指令
        case ID("ST") : m.seti(addr, R[ra]); c.log("m[%s]=%s", c.hex(addr,4), m.geti(addr)); break;       // 處理 ST 指令
        case ID("LDB"): R[ra] = m.getb(addr); break;         // 處理 LDB 指令
        case ID("STB"): m.setb(addr, R[ra]); break;        // 處理 STB 指令
        case ID("ADDI"):R[ra] = R[rb] + c16; break;         // 處理 ADDI 指令
        case ID("ADD"): R[ra] += m.geti(addr); break;             // 處理ADD指令
        case ID("SUB"): R[ra] -= m.geti(addr); break;             // 處理SUB指令
        case ID("MUL"): R[ra] *= m.geti(addr); break;             // 處理MUL指令
        case ID("DIV"): R[ra] /= m.geti(addr); break;             // 處理DIV指令
        case ID("AND"): R[ra] &= m.geti(addr); break;             // 處理AND指令
        case ID("OR") : R[ra] |= m.geti(addr); ; break;             // 處理OR指令
        case ID("XOR"): R[ra] ^= m.geti(addr); ; break;             // 處理XOR指令
        case ID("SHL"): R[ra] = R[rb]<<c5; break;             // 處理SHL指令
        case ID("SHR"): R[ra] = R[rb]>>c5; break;             // 處理SHR指令
        case ID("JZ") : if (R[ra]==0) R[PC] = R[rb]+c16; break;         // 處理JZ指令
        case ID("PUSH"):R[SP]-=4; R[ra]=m.geti(addr); m.seti(R[SP], R[ra]); break;   // 處理PUSH指令
        case ID("POP"): R[ra] = m.geti(R[SP]); R[SP]+=4; break;    // 處理POP指令
        case ID("PUSHB"):R[SP]--; R[ra]=m.getb(addr); m.setb(R[SP], R[ra]); break;    // 處理PUSH指令
        case ID("POPB"):R[ra] = m.getb(R[SP]); R[SP]++; break;      // 處理POPB指令
        case ID("RET"): stop=true; R[PC]=R[LR]; break;   // 處理RET指令
        default: c.log("Error:invalid op (%s)", hex(op));
      } // switch
      c.log("PC=%s IR=%s SW=%s R[%s]=0x%s=%d", // 印出 PC, IR, R[ra]暫存器的值，以利觀察
             c.hex(tpc,4), c.hex(R[IR],8), c.hex(R[SW],8), c.hex(ra,2), c.hex(R[ra], 8), R[ra]);
    } // while
}

run(process.argv[2]);
