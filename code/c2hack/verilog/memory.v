/* nand2tetris 的要求應該用下列方式實作，但是由於這樣元件太多會導致 icarus 編譯失敗，
出現下列訊息：

D:\Dropbox\cccweb\db\n2t>iverilog ram_test.v -o ram_test

This application has requested the Runtime to terminate it in an unusual way.
Please contact the application's support team for more information.

所以我們在記憶體容量大的時候改用 verilog 的陣列型寫法，這樣就不會當機了。 */
`include "alu.v"

module DFF (input in, clock, output out);
  reg q;
  assign out = q;
  always @(posedge clock) begin
    q = in;
  end
endmodule

module Bit(input in, clock, load, output out);
  wire dffin;
  Mux m1(out, in, load, dffin);
  DFF dff1(dffin, clock, out);
endmodule

module Register(input[15:0] in, input clock, load, output[15:0] out);
  Bit g01(in[15], clock, load, out[15]);
  Bit g02(in[14], clock, load, out[14]);
  Bit g03(in[13], clock, load, out[13]);
  Bit g04(in[12], clock, load, out[12]);
  Bit g05(in[11], clock, load, out[11]);
  Bit g06(in[10], clock, load, out[10]);
  Bit g07(in[9],  clock, load, out[9]);
  Bit g08(in[8],  clock, load, out[8]);
  Bit g09(in[7],  clock, load, out[7]);
  Bit g10(in[6],  clock, load, out[6]);
  Bit g11(in[5],  clock, load, out[5]);
  Bit g12(in[4],  clock, load, out[4]);
  Bit g13(in[3],  clock, load, out[3]);
  Bit g14(in[2],  clock, load, out[2]);
  Bit g15(in[1],  clock, load, out[1]);
  Bit g16(in[0],  clock, load, out[0]);
endmodule

module PC(input[15:0] in, input clock, load, inc, reset, output[15:0] out);
  wire[15:0] if1, if2, if3, oInc, o;
  
  Or g1(load, inc, loadInc);
  Or g2(loadInc, reset, loadIncReset);

  Inc16 inc1(o, oInc);
  And16 g3(o, o, out);
  
  Mux16 g4(o,   oInc,  inc,   if1);
  Mux16 g5(if1, in,    load,  if2);
  Mux16 g6(if2, 16'b0, reset, if3);

  Register reg1(if3, clock, loadIncReset, o);
endmodule

module RAM8(input[15:0] in, input clock, load, input[2:0] address, output[15:0] out);
  wire[15:0] o0,o1,o2,o3,o4,o5,o6,o7;
  
  DMux8Way g0(load, address, L0, L1, L2, L3, L4, L5, L6, L7);
  
  Register r0(in, clock, L0, o0);
  Register r1(in, clock, L1, o1);
  Register r2(in, clock, L2, o2);
  Register r3(in, clock, L3, o3);
  Register r4(in, clock, L4, o4);
  Register r5(in, clock, L5, o5);
  Register r6(in, clock, L6, o6);
  Register r7(in, clock, L7, o7);
  
  Mux8Way16 g1(o0, o1, o2, o3, o4, o5, o6, o7, address, out);
endmodule

module RAM64(input[15:0] in, input clock, load, input[5:0] address, output[15:0] out);
  wire[15:0] o0,o1,o2,o3,o4,o5,o6,o7;
  
  DMux8Way g0(load, address[5:3], L0, L1, L2, L3, L4, L5, L6, L7);
  
  RAM8 m0(in,  clock, L0, address[2:0], o0);
  RAM8 m1(in,  clock, L1, address[2:0], o1);
  RAM8 m2(in,  clock, L2, address[2:0], o2);
  RAM8 m3(in,  clock, L3, address[2:0], o3);
  RAM8 m4(in,  clock, L4, address[2:0], o4);
  RAM8 m5(in,  clock, L5, address[2:0], o5);
  RAM8 m6(in,  clock, L6, address[2:0], o6);
  RAM8 m7(in,  clock, L7, address[2:0], o7);

  Mux8Way16 g1(o0, o1, o2, o3, o4, o5, o6, o7, address[5:3], out);
endmodule

module ROM32K(input[14:0] address, output[15:0] out);
  reg[15:0] m[0:2**15-1];
  
  assign out = m[address];
endmodule

module RAM8K(input[15:0] in, input clock, load, input[12:0] address, output[15:0] out);
  reg[15:0] m[0:2**13-1];
  
  assign out = m[address];
  
  always @(posedge clock) begin
    if (load) m[address] = in;
  end
endmodule

module RAM16K(input[15:0] in, input clock, load, input[13:0] address, output[15:0] out);
  reg[15:0] m[0:2**14-1];
  
  assign out = m[address];
  
  always @(posedge clock) begin
    if (load) m[address] = in;
  end
endmodule

