`include "alu.v"

module main;
reg signed[15:0] x, y;
reg zx,nx,zy,ny,f,no;
wire signed[15:0] out;
wire zr, ng;

ALU alu1(x,y, zx,nx,zy,ny,f,no, out, zr,ng);

initial
begin
  $monitor("%4dns x=%d y=%d zx=%b nx=%b zy=%b ny=%b f=%b no=%b out=%d zr=%b ng=%b", $stime, x, y, zx, nx, zy, ny, f, no, out, zr, ng);
  x = 9;
  y = 15;
  zx = 0;
  nx = 0;
  zy = 0;
  ny = 0;
  f  = 0;
  no = 0;
end

always #320 begin
  zx = zx+1;
end

always #160 begin
  nx = nx+1;
end

always #80 begin
  zy = zy+1;
end

always #40 begin
  ny = ny+1;
end

always #20 begin
  f = f+1;
end

always #10 begin
  no = no+1;
end

initial #640 $finish;

endmodule