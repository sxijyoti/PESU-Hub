module circuit_1_tb;
    reg A, B, C;
    wire D, E;
    circuit_1 M1 (.A(A), .B(B), .C(C), .D(D), .E(E));
    initial begin
        A = 1'b0; B = 1'b0; C = 1'b0; #20;
        A = 1'b0; B = 1'b0; C = 1'b1; #20;
        A = 1'b0; B = 1'b1; C = 1'b0; #20;
        A = 1'b0; B = 1'b1; C = 1'b1; #20;
        A = 1'b1; B = 1'b0; C = 1'b0; #20;
        A = 1'b1; B = 1'b0; C = 1'b1; #20;
        A = 1'b1; B = 1'b1; C = 1'b0; #20;
        A = 1'b1; B = 1'b1; C = 1'b1; #20;
        #200;
        $finish;
    end
    initial begin
        $monitor($time, " A = %b, B = %b, C = %b, D = %b, E = %b", A, B, C, D, E);
    end
    initial begin
        $dumpfile("circuit_1.vcd");
        $dumpvars(0, circuit_1_tb);
    end
endmodule
