`include "gate16.v"

module main;
reg  [15:0] a,b;
wire [15:0] aNot, abAnd, abOr;

Not16  g1(a, aNot);
And16  g2(a, b, abAnd);
Or16   g3(a, b, abOr);

initial
begin
  $monitor("a  =%b\nb  =%b\nnot=%b\nand=%b\nor =%b", a, b, aNot, abAnd, abOr);
  a  = 16'b0011;
  b  = 16'b0101;
  $finish;
end

endmodule
