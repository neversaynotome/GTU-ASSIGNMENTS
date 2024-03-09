module PC(input clk, input [9:0] next_pc, input [9:0] branch_address, input branch, input jump, input jump_register, output reg [9:0] pc);
    always @(posedge clk) begin
        if (jump_register) begin
            pc <= next_pc;
        end
        else if (jump) begin
            pc <= branch_address;
        end
        else if (branch) begin
            pc <= pc + branch_address;
        end
        else begin
            pc <= pc + 4'b0001;
        end
    end
endmodule
