module ALU(input [3:0] aluop, input [15:0] op1, input [15:0] op2, output [15:0] result);
    // ALU operations
    wire [15:0] add_result, sub_result, and_result, or_result, sll_result, srl_result, mult_result;
    wire [15:0] slt_result, slti_result;
    wire equal, less_than;

    // ALU operation decoder
    always @* begin
        case (aluop)
            4'b0000: begin add_result = op1 + op2; result = add_result; end
            4'b0001: begin sub_result = op1 - op2; result = sub_result; end
            4'b0010: begin and_result = op1 & op2; result = and_result; end
            4'b0011: begin or_result = op1 | op2; result = or_result; end
            4'b0100: begin sll_result = op1 << op2[3:0]; result = sll_result; end
            4'b0101: begin srl_result = op1 >> op2[3:0]; result = srl_result; end
            4'b0110: begin mult_result = op1 * op2; result = mult_result; end
            4'b1000: begin slt_result = (op1 < op2) ? 16'h0001 : 16'h0000; result = slt_result; end
            4'b1001: begin slti_result = (op1 < op2[15:0]) ? 16'h0001 : 16'h0000; result = slti_result; end
        endcase
    end
endmodule
