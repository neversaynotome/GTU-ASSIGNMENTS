module instruction_decoder(clk, instruction, opcode, funct, rs, rt, rd, shamt, immediate, instruction_type, aluop, memop, branch);
    input clk;
    input [31:0] instruction;
    output [5:0] opcode;
    output [5:0] funct;
    output [3:0] rs, rt, rd, shamt;
    output [15:0] immediate;
    output [1:0] instruction_type;
    output [3:0] aluop;
    output [1:0] memop;
    output branch;
    
    wire [5:0] opcode_decoded;
    wire [3:0] rs_decoded, rt_decoded, rd_decoded, shamt_decoded;
    wire [15:0] immediate_decoded;
    wire [1:0] instruction_type_decoded;
    wire [3:0] aluop_decoded;
    wire [1:0] memop_decoded;
    wire branch_decoded;
    
    // instruction type decoder
    reg [1:0] instruction_type_reg;
    always @ (posedge clk) begin
        case (instruction[31:26])
            6'b000000: instruction_type_reg <= 2'b00; // R-type instruction
            6'b000010, 6'b000011: instruction_type_reg <= 2'b01; // J-type instruction
            6'b000100 to 6'b001001: instruction_type_reg <= 2'b10; // I-type instruction
            default: instruction_type_reg <= 2'b11; // Invalid instruction
        endcase
    end
    assign instruction_type = instruction_type_reg;
    
    // opcode decoder
    assign opcode = instruction[31:26];
    // funct decoder
    assign funct = instruction[5:0];
    // rs, rt, rd, shamt decoder
    assign rs = instruction[25:22];
    assign rt = instruction[21:18];
    assign rd = instruction[17:14];
    assign shamt = instruction[13:10];
    // immediate decoder
    assign immediate = instruction[15:0];
    
    // aluop decoder
    reg [3:0] aluop_reg;
    always @ (posedge clk) begin
        case (funct)
            6'b000000: aluop_reg <= 4'b0000; //add
            6'b000001: aluop_reg <= 4'b0001; //sub
            6'b001100: aluop_reg <= 4'b0010; //and
            6'b001101: aluop_reg <= 4'b0011; //or
            6'b000000: aluop_reg <= 4'b0100; //sll
            6'b000010: aluop_reg <= 4'b0101; //srl
            6'b011000: aluop_reg <= 4'b0110; //mult (bonus)
            default: aluop_reg <= 4'b1111; //invalid
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