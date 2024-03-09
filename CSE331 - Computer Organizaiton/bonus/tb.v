`timescale 1ns / 1ps

module cypher_detector_tb();

// Inputs
reg [15:0] cypher;
reg [3:0] input;
reg read;
reg reset;
reg clock;

// Outputs
wire [7:0] output;
wire cypher_detected;

// Instantiate cypher detector
cypher_detector dut(
  .cypher(cypher),
  .input(input),
  .read(read),
  .output(output),
  .cypher_detected(cypher_detected),
  .reset(reset),
  .clock(clock)
);

// Initialize inputs
initial begin
  cypher = 16'b0010_0110_0000_0001;
  input = 4'b0000;
  read = 1'b0;
  reset = 1'b0;
  clock = 1'b0;
end

// Clock period
parameter CLOCK_PERIOD = 10;

// Clock generator
always #(CLOCK_PERIOD / 2) clock = ~clock;

// Test input sequence
initial begin
  // Wait for reset to go high
  #(CLOCK_PERIOD * 10) reset = 1'b1;

  // Input sequence: 0000 0001 0011 0000 0011 0100 0001 0000 0010 0001 0001 0000 0110 0010
  #(CLOCK_PERIOD) input = 4'b0000; read = 1'b1;
  #(CLOCK_PERIOD) input = 4'b0001; read = 1'b1;
  #(CLOCK_PERIOD) input = 4'b0011; read = 1'b1;
  #(CLOCK_PERIOD) input = 4'b0000; read = 1'b1;
  #(CLOCK_PERIOD) input = 4'b0011; read = 1'b1;
  #(CLOCK_PERIOD) input = 4'b0100; read = 1'b1;
  #(CLOCK_PERIOD) input = 4'b0001; read = 1'b1;
  #(CLOCK_PERIOD) input = 4'b0000; read = 1'b1;
  #(CLOCK_PERIOD) input = 4'b0010; read = 1'b1;
  #(CLOCK_PERIOD) input = 4'b0001; read = 1'b1;
  #(CLOCK_PERIOD) input = 4'b0001; read = 1'b1;
  #(CLOCK_PERIOD) input = 4'b0000; read = 1'b1;
  #(CLOCK_PERIOD) input = 4'b0110; read = 1'b1;
  #(CLOCK_PERIOD) input = 4'b0010; read = 1'b1;
  
  // Wait for 1 second
  #(CLOCK_PERIOD * 100)
  
  // Stop simulation
  $stop;
end

endmodule