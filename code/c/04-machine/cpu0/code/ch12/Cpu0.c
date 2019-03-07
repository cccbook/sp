#include "Cpu0.h"

void runObjFile(char *objFile) {                 // 虛擬機器主函數
  printf("===VM0:run %s on CPU0===\n", objFile);               
  Cpu0 *cpu0 = Cpu0New(objFile);                 // 建立CPU0物件
  Cpu0Run(cpu0, 0);                              // 開始執行
  Cpu0Dump(cpu0);                                // 傾印暫存器
  Cpu0Free(cpu0);                                // 釋放記憶體 
}

Cpu0* Cpu0New(char *objFile) {                   // 建立 CPU0 物件                 
  Cpu0 *cpu0=ObjNew(Cpu0, 1);                    //  分配 CPU0 物件空間 
  cpu0->m = newFileBytes(objFile, &cpu0->mSize); //  載入映像檔 objFile 到記憶體 m 中
  return cpu0;                                                                
}                                                                             
                                                                              
void Cpu0Free(Cpu0 *cpu0) {                      // 刪除 CPU0 物件                 
  freeMemory(cpu0->m);                           //  釋放 CPU0 的 memory 
  ObjFree(cpu0);                                 //  釋放 CPU0 物件                                         
}                                                                                         
                                                                                                                                                            
#define bits(i, from, to) ((UINT32) i << (31-to) >> (31-to+from)) // 取得 from 到 to 之間的位元                   
#define ROR(i, k) (((UINT32)i>>k)|(bits(i,32-k, 31)<<(32-k)))// 向右旋轉k位元                                           
#define ROL(i, k) (((UINT32)i<<k)|(bits(i,0,k-1)<<(32-k)))   // 向左旋轉k位元                                             
#define SHR(i, k) ((UINT32)i>>k)                             // 向右移位k位元                
#define SHL(i, k) ((UINT32)i<<k)                             // 向左移位k位元                
#define bytesToInt32(p) (INT32)(p[0]<<24|p[1]<<16|p[2]<<8|p[3])// 4 byte轉 int
#define bytesToInt16(p) (INT16)(p[0]<<8|p[1])                // 2 byte轉 INT16               
#define int32ToBytes(i, bp) { bp[0]=i>>24; bp[1]=i>>16; bp[2]=i>>8; bp[3]=i;} // int轉為4 byte                                             
#define StoreInt32(i, m, addr) { BYTE *p=&m[addr]; int32ToBytes(i, p); } // i=m[addr…addr+3]                                         
#define LoadInt32(i, m, addr) { BYTE *p=&m[addr]; i=bytesToInt32(p); } // m[addr..addr+3]=i                                         
#define StoreByte(b, m, addr) { m[addr] = (BYTE) b; }        // m[addr]=b                                                 
#define LoadByte(b, m, addr) { b = m[addr]; }                // b=m[addr]                    
                                                                                          
#define PC R[15]                                             // PC is R[15]                  
#define LR R[14]                                             // LR is R[14]                  
#define SP R[13]                                             // SP is R[13]                  
#define SW R[12]                                             // SW is R[12]                  

void Cpu0Run(Cpu0 *cpu0, int start) {                        // 虛擬機器的主要執行函數                   
  char buffer[200];
  unsigned int IR, op, ra, rb, rc, cc;                                                                         
  int c5, c12, c16, c24, caddr, raddr;                                                                
  unsigned int N, Z;
  BYTE *m=cpu0->m;                                                                                    
  int  *R=cpu0->R;                                           
  PC = start;                                                // 設定起始位址，準備開始執行                             
  LR = -1;                                                                                
  BOOL stop = FALSE;                                                                                  
  while (!stop) {                                            // 如果尚未結束                             
    R[0] = 0;                                                // R[0] 永遠為 0                            
    LoadInt32(IR, m, PC);                                    // 指令擷取，IR=[PC..PC+3]                                 
    cpu0->IR = IR;                                           // 取得指令暫存器                           
    PC += 4;                                                 // 擷取完將 PC 加 4，指向下一個指令
    op = bits(IR, 24, 31);                                   // 取得 op 欄位，IR[24..31]
    ra = bits(IR, 20, 23);                                   // 取得 ra 欄位，IR[20..23]    
    rb = bits(IR, 16, 19);                                   // 取得 rb 欄位，IR[16..19]
    rc = bits(IR, 12, 15);                                   // 取得 rc 欄位，IR[12..15]
    c5 = bits(IR,  0, 4);                                    // 取得 5  位元的 cx 
    c12= bits(IR, 0, 11);                                    // 取得 12 位元的 cx 
    c16= bits(IR, 0, 15);                                    // 取得 16 位元的 cx                         
    c24= bits(IR, 0, 23);                                    // 取得 24 位元的 cx                                         
    N  = bits(SW, 31, 31);
    Z  = bits(SW, 30, 30);
    if (bits(IR, 11, 11)!=0) c12 |= 0xFFFFF000;              // 若 cx 為負數，則調整為2補數格式                                         
    if (bits(IR, 15, 15)!=0) c16 |= 0xFFFF0000;              // 若 cx 為負數，則調整為2補數格式                                        
    if (bits(IR, 23, 23)!=0) c24 |= 0xFF000000;              // 若 cx 為負數，則調整為2補數格式                                                                                 
    caddr = R[rb]+c16;                                       // 取得位址[Rb+cx]                          
    raddr = R[rb]+R[rc];                                     // 取得位址[Rb+Rc]                          
    switch (op) {                                            // 根據op執行動作                           
      case OP_LD : LoadInt32(R[ra], m, caddr); break;        // 處理 LD 指令                            
      case OP_ST : StoreInt32(R[ra], m, caddr); break;       // 處理 ST 指令                            
      case OP_LDB: LoadByte(R[ra], m, caddr); break;         // 處理 LDB 指令                            
      case OP_STB: StoreByte(R[ra], m, caddr); break;        // 處理 STB 指令                            
      case OP_LDR: LoadInt32(R[ra], m, raddr); break;        // 處理 LDR 指令                           
      case OP_STR: StoreInt32(R[ra], m, raddr); break;       // 處理 STR 指令                           
      case OP_LBR: LoadByte(R[ra], m, raddr); break;         // 處理 LBR 指令                           
      case OP_SBR: StoreByte(R[ra], m, raddr); break;        // 處理 SBR 指令                           
      case OP_LDI: R[ra] = c16; break;                       // 處理 LDI 指令                           
      case OP_CMP: {                                         // 處理CMP指令，根據比較結果，設定 N,Z 旗標 
        if (R[ra] > R[rb]) {                                 // > : SW(N=0, Z=0)
          SW &= 0x3FFFFFFF;                                  // N=0, Z=0
        } else if (R[ra] < R[rb]) {                          // < : SW(N=1, Z=0, ....)                                                
          SW |= 0x80000000;                                  // N=1;
          SW &= 0xBFFFFFFF;                                  // Z=0;
        } else {                                             // = : SW(N=0, Z=1)                      
          SW &= 0x7FFFFFFF;                                  // N=0;
          SW |= 0x40000000;                                  // Z=1;
        }
        ra = 12;
        break;                                                                                        
      } case OP_MOV: R[ra] = R[rb]; break;                   // 處理MOV指令                             
      case OP_ADD: R[ra] = R[rb] + R[rc]; break;             // 處理ADD指令                             
      case OP_SUB: R[ra] = R[rb] - R[rc]; break;             // 處理SUB指令                             
      case OP_MUL: R[ra] = R[rb] * R[rc]; break;             // 處理MUL指令                             
      case OP_DIV: R[ra] = R[rb] / R[rc]; break;             // 處理DIV指令                             
      case OP_AND: R[ra] = R[rb] & R[rc]; break;             // 處理AND指令                             
      case OP_OR:  R[ra] = R[rb] | R[rc]; break;             // 處理OR指令                              
      case OP_XOR: R[ra] = R[rb] ^ R[rc]; break;             // 處理XOR指令                             
      case OP_ROL: R[ra] = ROL(R[rb],c5); break;             // 處理ROL指令                             
      case OP_ROR: R[ra] = ROR(R[rb],c5); break;             // 處理ROR指令                             
      case OP_SHL: R[ra] = SHL(R[rb],c5); break;             // 處理SHL指令                             
      case OP_SHR: R[ra] = SHR(R[rb],c5); break;             // 處理SHR指令                             
      case OP_JEQ: if (Z==1) PC += c24; break;               // 處理JEQ指令 Z=1
      case OP_JNE: if (Z==0) PC += c24; break;               // 處理JNE指令 Z=0 
      case OP_JLT: if (N==1&&Z==0) PC += c24; break;         // 處理JLT指令 NZ=10 
      case OP_JGT: if (N==0&&Z==0) PC += c24; break;         // 處理JGT指令 NZ=00
      case OP_JLE:                                           // 處理JLE指令 NZ=10 or 01
           if ((N==1&&Z==0)||(N==0&&Z==1)) PC+=c24; break;
      case OP_JGE:                                           // 處理JGE指令 NZ=00 or 01
           if ((N==0&&Z==0)||(N==0&&Z==1)) PC+=c24; break;
      case OP_JMP: PC+=c24; break;                           // 處理JMP指令                             
      case OP_SWI: LR = PC; PC=c24; break;                   // 處理SWI指令                             
      case OP_JSUB:LR = PC; PC+=c24; break;                  // 處理JSUB指令                            
      case OP_RET: if (LR<0) stop=TRUE; else PC=LR; break;   // 處理RET指令                             
      case OP_PUSH:SP-=4; StoreInt32(R[ra], m, SP); break;   // 處理PUSH指令                            
      case OP_POP: LoadInt32(R[ra], m, SP); SP+=4; break;    // 處理POP指令                             
      case OP_PUSHB:SP--; StoreByte(R[ra], m, SP); break;    // 處理PUSH指令                            
      case OP_POPB:LoadByte(R[ra], m, SP); SP++; break;      // 處理POPB指令                            
      default: printf("Error:invalid op (%02x) ", op);                                                
    }                                                                                                 
    sprintf(buffer, "PC=%08x IR=%08x SW=%08x R[%02d]=0x%08x=%d\n", // 印出 PC, IR, R[ra]暫存器的值，以利觀察
                         PC,      IR,     SW,  ra,    R[ra],R[ra]);
    strToUpper(buffer);
    printf(buffer);
  }                                                                                                   
}                                                                                       
                                                                                        
void Cpu0Dump(Cpu0 *cpu0) {                                  // 印出所有暫存器                           
  printf("\n===CPU0 dump registers===\n");                                                            
  printf("IR =0x%08x=%d\n", cpu0->IR, cpu0->IR);             // 印出 IR                                                                           
  int i;                                                                   
  for (i=0; i<16; i++)                                       // 印出 R0..R15  
    printf("R[%02d]=0x%08x=%d\n",i,cpu0->R[i],cpu0->R[i]);
}