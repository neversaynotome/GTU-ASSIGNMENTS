module control_unit(clk, instruction, instruction_type, opcode, funct, aluop, memop, branch);
    input clk;
    input [31:0] instruction;
    input [1:0] instruction_type;
    input [5:0] opcode, funct;
    output [3:0] aluop;
    output [1:0] memop;
    output branch;

    wire [3:0] aluop_decoded;
    wire [1:0] memop_decoded;
    wire branch_decoded;

    // aluop decoder
    reg [3:0] aluop_reg;
    always @ (posedge clk) begin
        case ( {instruction_type,opcode} )
            2'b00: aluop_reg <= 4'b0000; // R-Type instruction add
            2'b10: aluop_reg <= 4'b0001; // I-Type instruction addi
            2'b00: aluop_reg <= 4'b0010; // R-Type instruction and
            2'b10: aluop_reg <= 4'b0011; // I-Type instruction andi
            2'b00: aluop_reg <= 4'b0100; // R-Type instruction sll
            2'b00: aluop_reg <= 4'b0101; // R-Type instruction srl
            2'b00: aluop_reg <= 4'b0110; // R-Type instruction mult (bonus)
            default: aluop_reg <= 4'b1111; // Invalid instruction
        endcase
    end
    assign aluop = aluop_reg;

    // memop decoder
    reg [1:0] memop_reg;
    always @ (posedge clk) begin
        case (opcode)
            6'b100011: memop_reg <= 2'b00; //lw
            6'b101011: memop_reg <= 2'b01; //sw
            default: memop_reg <= 2'b10; //not a memory instruction
        endcase
    end
    assign memop = memop_reg;
    
    // branch decoder
    reg branch_reg;
    always @ (posedge clk) begin
        case (opcode)
            6'b000100: branch_reg <= 1'b1; //beq
            6'b000101: branch_reg <= 1'b1; //bne
            default: branch_reg <= 1'b0; //not a branch instruction
        endcase
    end
    assign branch = branch_reg;
endmodule
