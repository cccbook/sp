`include "memory.v"

module main;
reg[15:0] in;
reg       load, clock;
reg[13:0] address;
wire[15:0] out;

RAM16K m(in, clock, load, address, out);

initial
begin
  clock=0;
  $monitor("%4dns in=%d clock=%d load=%d address=%d out=%d", $stime, in, clock, load, address, out);
  #10 in=3; load=1; address=5;
  #10 load=0; 
  #10	$finish;
end

always #2 begin
  clock=~clock;
end

endmodule
