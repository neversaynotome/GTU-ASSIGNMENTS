module data_memory(input clk, input [1:0] memop, input [15:0] address, input [15:0] write_data, output [15:0] read_data);
    reg [15:0] memory [65535:0]; // 2^16 words of memory

    always @(posedge clk) begin
        case (memop)
            2'b00: begin read_data <= memory[address]; end // lw instruction
            2'b01: begin memory[address] <= write_data; end // sw instruction
        endcase
    end
endmodule
