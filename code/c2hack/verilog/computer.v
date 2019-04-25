`include "memory.v"

module Memory(input[15:0] in, input clock, load, input[14:0] address, output[15:0] out);
  wire[15:0] outM, outS, outK, outSK;
  
  Not g1(address[14], N14);
  And g2(N14, load, Mload);
  And g3(address[14], load, Sload);
  
  RAM16K ram16k(in, clock, Mload, address[13:0], outM);
  RAM8K  screen(in, clock, Sload, address[12:0], outS);
  Register keyboard(16'h0F0F, clock, 1'b0, outK);
  
  Mux16 g4(outM, outSK, address[14], out);
  Mux16 g5(outS, outK,  address[13], outSK);
endmodule

module CPU(input[15:0] inM, I, input clock, reset, output[15:0] outM, output writeM, output[14:0] addressM, pc);
  wire[15:0] Ain, Aout, AorM, ALUout, Dout, pcOut, addressMOut;
  Or  g1(ng, zr, ngzr);   // ngzr = (ng|zr)
  Not g2(ngzr, g);     // g = out > 0 = !(ng|zr);  ng = out < 0;  zr = out = 0
  And g3(ng, I[2], passLT);    // ngLT = (ng&LT)
  And g4(zr, I[1], passEQ);    // zrEQ = (zr&EQ)
  And g5(g,  I[0], passGT);    // gGT = (g&GT)
  Or  g6(passLT, passEQ, passLE);
  Or  g7(passLE, passGT, pass);

  And g8(I[15], pass, PCload);     // PCload = I15&J
  
  // ALU
  Mux16 g9(Aout, inM, I[12], AorM); // Mux ALU in : cAorM = I[12]
  
  ALU alu(Dout, AorM, I[11], I[10], I[9], I[8], I[7], I[6], ALUout, zr, ng);
  
  PC pc1(Aout, clock, PCload, 1'b1, reset, pcOut);
  assign pc = pcOut[14:0];
  
  // A register
  Not g10(I[15], Atype);
  And g11(I[15], I[5], AluToA); // AluToA = I[15]&d1
  Or  g12(Atype, AluToA, Aload);
  
  Mux16 g13(I, ALUout, AluToA, Ain); // sel=I[15]
  Register A(Ain, clock, Aload, Aout);
  
  // D register
  And g14(I[15], I[4], Dload); // Aload = I[15]&d2
  Register D(ALUout, clock, Dload, Dout);
  
  // output
  assign addressM = Aout[14:0];
  And g16(I[15], I[3], writeM); // writeM = I[15] & d3
  And16 g17(ALUout, ALUout, outM);
endmodule

module Computer(input clock, reset);
  wire[15:0] inM, outM, I;
  wire[14:0] addressM, pc;
  
  Memory ram(inM, !clock, loadM, addressM, outM);
  ROM32K rom(pc, I);
  CPU    cpu(outM, I, clock, reset, inM, loadM, addressM, pc);	
endmodule
