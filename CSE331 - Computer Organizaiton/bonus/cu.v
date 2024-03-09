module control_unit(
  input wire [15:0] cypher,
  input wire [3:0] input,
  input wire read,
  output wire compare_enable,
  output wire input_register_enable,
  output wire cypher_register_enable,
  output wire output_enable,
  output wire cypher_detected,
  input wire reset,
  input wire clock
);

// Declare state registers
reg [1:0] state;

// Declare counter to keep track of which 4 bits of the cypher have been compared
reg [3:0] cypher_counter;

// Declare output registers
reg compare_enable_reg;
reg input_register_enable_reg;
reg cypher_register_enable_reg;
reg output_enable_reg;
reg cypher_detected_reg;

// Update state and output registers based on current state and inputs
always @(posedge clock or negedge reset) begin
  if (!reset) begin
    // Reset state and output registers to 0 on negative edge of reset
    state <= 2'b0;
    cypher_counter <= 4'b0;
    compare_enable_reg <= 1'b0;
    input_register_enable_reg <= 1'b0;
    cypher_register_enable_reg <= 1'b0;
    output_enable_reg <= 1'b0;
    cypher_detected_reg <= 1'b0;
  end else begin
    case (state)
      // State 0: Cypher not yet detected
      2'b0: begin
        // Update state based on read input and 4-bit input
        if (read && (input == cypher[3:0])) begin
          state <= 2'b1;
        end else if (read) begin
          state <= 2'b0;
        end
        // Update output registers
        compare_enable_reg <= 1'b0;
        input_register_enable_reg <= 1'b1;
        cypher_register_enable_reg <= 1'b0;
        output_enable_reg <= 1'b0;
        cypher_detected_reg <= 1'b0;
      end
      // State 1: Cypher detected
      2'b1: begin
        // Update state based on read input
        if (read) begin
          state <= 2'b1;
        end
        // Update output registers
        compare_enable_reg <= 1'b0;
        input_register_enable_reg <= 1'b1;
        cypher_register_enable_reg <= 1'b0;
        output_enable_reg <= 1'b1;
        cypher_detected_reg <= 1'b1;
      end
    endcase
  end
end

// Assign output registers to output signals
assign compare_enable = compare_enable_reg;
assign input_register_enable = input_register_enable_reg;
assign cypher_register_enable = cypher_register_enable_reg;
assign output_enable = output_enable_reg;
assign cypher_detected = cypher_detected_reg;

endmodule