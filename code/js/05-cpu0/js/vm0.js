var c = require("./ccc");
var cpu1 = require("./cpu0");
var Memory = require("./memory");

var isDump = process.argv[3] == "-d";

var IR = 16, PC = 15, LR = 14, SP = 13, SW = 12;
var ID = function(op) { return cpu1.opTable[op].id; }

var run = function(objFile) {
    R = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 13, -1, 0, 16];
    m = new Memory(1);
    m.load(objFile);
    if (isDump) m.dump();
    var stop = false;
    while (!stop) {                                          // 如果尚未結束
      var tpc = R[PC];
      R[0] = 0;                                              // R[0] 永遠為 0
      R[IR] = m.geti(R[PC]);                                 // 指令擷取，IR=[PC..PC+3]
      R[PC] += 4;                                            // 擷取完將 PC 加 4，指向下一個指令
      var op = c.bits(R[IR], 24, 31);                        // 取得 op 欄位，IR[24..31]
      var ra = c.bits(R[IR], 20, 23);                        // 取得 ra 欄位，IR[20..23]
      var rb = c.bits(R[IR], 16, 19);                        // 取得 rb 欄位，IR[16..19]
      var rc = c.bits(R[IR], 12, 15);                        // 取得 rc 欄位，IR[12..15]
      var c24= c.signbits(R[IR], 0,  23);                    // 取得 24 位元的 cx
      var c16= c.signbits(R[IR], 0,  15);                    // 取得 16 位元的 cx
      var c5 = c.bits(R[IR], 0,   4);                        // 取得 16 位元的 cx
      var addr  = R[rb]+c16;
      var raddr = R[rb]+R[rc];                               // 取得位址[Rb+Rc]                          
      var N  = c.bits(R[SW], 31, 31);
      var Z  = c.bits(R[SW], 30, 30);
//      c.log("IR=%s ra=%d rb=%d rc=%d c24=%s c16=%s addr=%s", c.hex(R[IR], 8), ra, rb, rc, c.hex(c24, 6), c.hex(c16, 4), c.hex(addr, 8))
      switch (op) {                                          // 根據op執行動作
        case ID("LD") : R[ra] = m.geti(addr); break;         // 處理 LD 指令
        case ID("ST") :                                      // 處理 ST 指令
          m.seti(addr, R[ra]); 
          if (isDump) c.log("m[%s]=%s", c.hex(addr,4), m.geti(addr)); 
          break;
        case ID("LDB"): R[ra] = m.getb(addr); break;         // 處理 LDB 指令
        case ID("STB"): m.setb(addr, R[ra]); break;          // 處理 STB 指令
        case ID("LDR"): R[ra] = m.geti(raddr); break;        // 處理 LDR 指令
        case ID("STR"): m.seti(raddr, R[ra]); break;         // 處理 STR 指令
        case ID("LBR"): R[ra] = m.getb(raddr); break;        // 處理 LBR 指令
        case ID("SBR"): m.setb(raddr, R[ra]); break;         // 處理 SBR 指令
        case ID("LDI"): R[ra] = c16; break;                  // 處理 LDI 指令
        case ID("CMP"): {                                    // 處理 CMP指令，根據比較結果，設定 N,Z 旗標 
          if (R[ra] > R[rb]) {                               // > : SW(N=0, Z=0)
            R[SW] &= 0x3FFFFFFF;                             // N=0, Z=0
          } else if (R[ra] < R[rb]) {                        // < : SW(N=1, Z=0, ....)                                                
            R[SW] |= 0x80000000;                             // N=1;
            R[SW] &= 0xBFFFFFFF;                             // Z=0;
          } else {                                           // = : SW(N=0, Z=1)                      
            R[SW] &= 0x7FFFFFFF;                             // N=0;
            R[SW] |= 0x40000000;                             // Z=1;
          }
          ra = 12;
          break;                                                                                        
        }
        case ID("MOV"): R[ra] = R[rb]; break;                // 處理MOV指令
        case ID("ADD"): R[ra] = R[rb]+R[rc]; break;          // 處理ADD指令
        case ID("SUB"): R[ra] = R[rb]-R[rc]; break;          // 處理SUB指令
        case ID("MUL"): R[ra] = R[rb]*R[rc]; break;          // 處理MUL指令
        case ID("DIV"): R[ra] = R[rb]/R[rc]; break;          // 處理DIV指令
        case ID("AND"): R[ra] = R[rb]&R[rc]; break;          // 處理AND指令
        case ID("OR") : R[ra] = R[rb]|R[rc]; break;          // 處理OR指令
        case ID("XOR"): R[ra] = R[rb]^R[rc]; break;          // 處理XOR指令
        case ID("SHL"): R[ra] = R[rb]<<c5; break;            // 處理SHL指令
        case ID("SHR"): R[ra] = R[rb]>>c5; break;            // 處理SHR指令
        case ID("ADDI"):R[ra] = R[rb] + c16; break;          // 處理 ADDI 指令
        case ID("JEQ"): if (Z==1) R[PC] += c24; break;       // 處理JEQ指令 Z=1
        case ID("JNE"): if (Z==0) R[PC] += c24; break;       // 處理JNE指令 Z=0 
        case ID("JLT"): if (N==1&&Z==0) R[PC] += c24; break; // 處理JLT指令 NZ=10 
        case ID("JGT"): if (N==0&&Z==0) R[PC] += c24; break; // 處理JGT指令 NZ=00
        case ID("JLE"): if ((N==1&&Z==0)||(N==0&&Z==1)) R[PC]+=c24; break; // 處理JLE指令 NZ=10 or 01
        case ID("JGE"): if ((N==0&&Z==0)||(N==0&&Z==1)) R[PC]+=c24; break; // 處理JGE指令 NZ=00 or 01
        case ID("JMP"): R[PC]+=c24; break;                   // 處理JMP指令                             
        case ID("SWI"):                                      // 處理SWI指令
            switch (c24) {
                case 3: c.printf("%s", m.getstr(R[9])); break;
                case 4: c.printf("%d", R[9]); break;
                default: 
                    var emsg = c.format("SWI cx=%d not found!", c24); 
                    c.error(emsg, null); 
                    break;
            }
            break;
        case ID("JSUB"):R[LR] = R[PC]; R[PC]+=c24; break;    // 處理JSUB指令
        case ID("RET"): if (R[LR]<0) stop=true; else R[PC]=LR; break; // 處理RET指令
        case ID("PUSH"):R[SP]-=4; R[ra]=m.geti(addr); m.seti(R[SP], R[ra]); break; // 處理PUSH指令
        case ID("POP"): R[ra] = m.geti(R[SP]); R[SP]+=4; break;     // 處理POP指令
        case ID("PUSHB"):R[SP]--; R[ra]=m.getb(addr); m.setb(R[SP], R[ra]); break; // 處理PUSH指令
        case ID("POPB"):R[ra] = m.getb(R[SP]); R[SP]++; break;      // 處理POPB指令
        default: c.error("OP not found!", null);
      } // switch
      if (isDump) 
        c.log("PC=%s IR=%s SW=%s R[%s]=0x%s=%d", // 印出 PC, IR, R[ra]暫存器的值，以利觀察
              c.hex(tpc,4), c.hex(R[IR],8), c.hex(R[SW],8), c.hex(ra,2), c.hex(R[ra], 8), R[ra]);
    } // while
}

run(process.argv[2]);
