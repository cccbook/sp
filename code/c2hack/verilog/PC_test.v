`include "memory.v"

module main;
reg[15:0] in;
reg load, inc, reset, clock;
wire[15:0] out;

PC pc(in, clock, load, inc, reset, out);

initial
begin
  clock = 0;
  $monitor("%4dns clock=%d in=%d reset=%d inc=%d load=%d out=%d", $stime, clock, in, reset, inc, load, out);
  inc = 0; load = 0; reset=0; in=7;
  #10 reset=1; inc=1; 
  #10 reset=0;
  #10 reset=0;
  #30 inc = 0; load=1;
  #30 load = 0; inc=1;
  #30	$finish;
end

always #2 begin
  clock = clock + 1;
end

endmodule