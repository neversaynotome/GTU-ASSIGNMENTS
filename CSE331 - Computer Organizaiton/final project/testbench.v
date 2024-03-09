module testbench();
    reg clk;
    reg [31:0] instruction;
    reg [15:0] write_data;
    reg [15:0] address;
    wire [15:0] read_data;
    wire [3:0] aluop;
    wire [1:0] memop;
    wire [9:0] pc;
    wire branch;
    wire jump;
    wire jump_register;
    // Instantiate the design
    processor dut(clk, instruction, write_data, address, read_data, aluop, memop, pc, branch, jump, jump_register);
    initial begin
        clk = 0;
        instruction = 32'h0000_0000_0000_0000;
        write_data = 16'h0000;
        address = 16'h0000;
        #10;
        clk = 1;
        #10;
        clk = 0;
        instruction = 32'h0000_0000_0000_0000;
        write_data = 16'h0000;
        address = 16'h0000;
    end
    // test case 1
    initial begin
        #100;
        instruction = 32'h0000_0000_0000_0000; // add $0, $0, $0
        #100;
        instruction = 32'h0000_0000_0000_0000; // nop
        #100;
        instruction = 32'h0000_0000_0000_0000; // nop
        #100;
        instruction = 32'h0000_0000_0000_0000; // nop
        #100;
        instruction = 32'h0000_0000_0000_0000; // nop
        #100;
        instruction = 32'h0000_0000_0000_0000; // nop
    end
    // test case 2
    initial begin
        #100;
        instruction = 32'h0000_0001_0000_0010; // addi $1, $0, 2
        #100;
        instruction = 32'h0000_0000_0001_0001; // add $1, $0, $1
        #100;
        instruction = 32'h0000_0000_0001_0001; // add $1, $0, $1
    end
    // more test cases can be added here
    // ...
endmodule
