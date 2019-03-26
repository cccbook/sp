`include "gate.v"

module Not16(input[15:0] in, output[15:0] out);
  Not g15(in[15], out[15]);
  Not g14(in[14], out[14]);
  Not g13(in[13], out[13]);
  Not g12(in[12], out[12]);
  Not g11(in[11], out[11]);
  Not g10(in[10], out[10]);
  Not g09(in[9], out[9]);
  Not g08(in[8], out[8]);
  Not g07(in[7], out[7]);
  Not g06(in[6], out[6]);
  Not g05(in[5], out[5]);
  Not g04(in[4], out[4]);
  Not g03(in[3], out[3]);
  Not g02(in[2], out[2]);
  Not g01(in[1], out[1]);
  Not g00(in[0], out[0]);
endmodule

module And16(input[15:0] a, b, output[15:0] out);
  And g15(a[15], b[15], out[15]);
  And g14(a[14], b[14], out[14]);
  And g13(a[13], b[13], out[13]);
  And g12(a[12], b[12], out[12]);
  And g11(a[11], b[11], out[11]);
  And g10(a[10], b[10], out[10]);
  And g09(a[9], b[9], out[9]);
  And g08(a[8], b[8], out[8]);
  And g07(a[7], b[7], out[7]);
  And g06(a[6], b[6], out[6]);
  And g05(a[5], b[5], out[5]);
  And g04(a[4], b[4], out[4]);
  And g03(a[3], b[3], out[3]);
  And g02(a[2], b[2], out[2]);
  And g01(a[1], b[1], out[1]);
  And g00(a[0], b[0], out[0]);
endmodule

module Or16(input[15:0] a, b, output[15:0] out);
  Or g15(a[15], b[15], out[15]);
  Or g14(a[14], b[14], out[14]);
  Or g13(a[13], b[13], out[13]);
  Or g12(a[12], b[12], out[12]);
  Or g11(a[11], b[11], out[11]);
  Or g10(a[10], b[10], out[10]);
  Or g09(a[9], b[9], out[9]);
  Or g08(a[8], b[8], out[8]);
  Or g07(a[7], b[7], out[7]);
  Or g06(a[6], b[6], out[6]);
  Or g05(a[5], b[5], out[5]);
  Or g04(a[4], b[4], out[4]);
  Or g03(a[3], b[3], out[3]);
  Or g02(a[2], b[2], out[2]);
  Or g01(a[1], b[1], out[1]);
  Or g00(a[0], b[0], out[0]);
endmodule

