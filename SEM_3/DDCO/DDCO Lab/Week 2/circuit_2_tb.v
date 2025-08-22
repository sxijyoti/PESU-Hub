module circuit_2_tb;
    reg A, B, C;
    wire D;
    circuit_2 M1 (.A(A), .B(B), .C(C), .D(D));
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
        $monitor($time, " A = %b, B = %b, C = %b, D = %b", A, B, C, D);
    end
    initial begin
        $dumpfile("circuit_2.vcd");
        $dumpvars(0, circuit_2_tb);
    end
endmodule
