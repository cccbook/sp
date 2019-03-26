`include "mux.v"

module HalfAdder(input a,b, output sum, carry);
  Xor g1(a, b, sum);
  And g2(a, b, carry);
endmodule

module FullAdder(input a,b,c, output sum, carry);
  wire s1, c1, c2;
  Xor g1(a,  b,  s1);
  Xor g2(s1, c,  sum);
  And g3(a,  b,  c1);
  And g4(s1, c,  c2);
  Xor g5(c2, c1, carry);
endmodule

module Add16(input[15:0] a,b, output[15:0] out);
  wire [15:0] c;
  FullAdder g01(a[0],  b[0],  1'b0,  out[0],  c[0]);
  FullAdder g02(a[1],  b[1],  c[0],  out[1],  c[1]);
  FullAdder g03(a[2],  b[2],  c[1],  out[2],  c[2]);
  FullAdder g04(a[3],  b[3],  c[2],  out[3],  c[3]);
  FullAdder g05(a[4],  b[4],  c[3],  out[4],  c[4]);
  FullAdder g06(a[5],  b[5],  c[4],  out[5],  c[5]);
  FullAdder g07(a[6],  b[6],  c[5],  out[6],  c[6]);
  FullAdder g08(a[7],  b[7],  c[6],  out[7],  c[7]);
  FullAdder g09(a[8],  b[8],  c[7],  out[8],  c[8]);
  FullAdder g10(a[9],  b[9],  c[8],  out[9],  c[9]);
  FullAdder g11(a[10], b[10], c[9],  out[10], c[10]);  
  FullAdder g12(a[11], b[11], c[10], out[11], c[11]);   
  FullAdder g13(a[12], b[12], c[11], out[12], c[12]);   
  FullAdder g14(a[13], b[13], c[12], out[13], c[13]);   
  FullAdder g15(a[14], b[14], c[13], out[14], c[14]);   
  FullAdder g16(a[15], b[15], c[14], out[15], c[15]);
endmodule

module Inc16(input[15:0] in, output[15:0] out);
  Add16 g1(in, 16'h1, out);
endmodule

//  x[16], y[16],  // 16-bit inputs  
//  zx, // zero the x input?
//  nx, // negate the x input?
//  zy, // zero the y input?
//  ny, // negate the y input?
//  f,  // compute out = x + y (if 1) or x & y (if 0)
//  no; // negate the out output?
//  out[16], zr, ng;  // zr:zero, ng:negative

module ALU(input[15:0] x, y, input zx,nx,zy,ny,f,no, output[15:0] out, output zr, ng);
  wire[15:0] x1, notx1, x2, y1, noty1, y2, andxy, addxy, o1, noto1, o2;
  wire orLow, orHigh, notzr;
  
  Mux16 g1(x,  16'b0, zx, x1);   // if (zx == 1) set x = 0  
  Not16 g2(x1, notx1);
  Mux16 g3(x1, notx1, nx, x2);   // if (nx == 1) set x = !x
  
  Mux16 g4(y,  16'b0, zy, y1);   // if (zy == 1) set y = 0
  Not16 g5(y1, noty1);
  Mux16 g6(y1, noty1, ny, y2);   // if (ny == 1) set y = !y
  
  Add16 g7(x2, y2, addxy);       // addxy = x + y
  And16 g8(x2, y2, andxy);       // andxy = x & y
  
  Mux16 g9(andxy, addxy, f, o1); // if (f == 1)  set out = x + y else set out = x & y
  Not16 g10(o1, noto1);
  
  Mux16 g11(o1, noto1, no, o2);   // if (no == 1) set out = !out
  
  // o2 就是 out, 但必須中間節點才能再次當作輸入，所以先用 o2。
  And16 g12(o2, o2, out); 
  Or8Way g13(out[7:0],  orLow);  // orLow = Or(out[0..7]);
  Or8Way g14(out[15:8], orHigh);// orHigh = Or(out[8..15]);
  Or    g15(orLow, orHigh, notzr);  // nzr = Or(out[0..15]);
  Not   g16(notzr, zr);            // zr = !nzr
  And   g17(o2[15], o2[15], ng);   // ng = out[15]
  And16 g18(o2, o2, out);
endmodule
