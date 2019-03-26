`include "computer.v"

module main;
reg reset, clock;

Computer c(clock, reset);

integer i;

initial
begin
  $readmemb("sum.hack", c.rom.m);
  for (i=0; i < 32; i=i+1) begin
    $display("%4x: %x", i, c.rom.m[i]);
  end
  $monitor("%4dns clock=%d pc=%d I=%d A=%d D=%d M=%d", $stime, clock, c.pc, c.I, c.addressM, c.cpu.Dout, c.outM);
  clock = 0;
  #10 reset=1;
  #30 reset=0;
end

always #5 begin
  clock = clock + 1;
end

initial #1800 $finish;

endmodule
