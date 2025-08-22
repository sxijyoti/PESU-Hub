module mux21tb;
    reg A,B,S;
    wire X;
    mux21 m1(.i0(A),.i1(B),.j(S),.o(X));
    initial
    begin
        A = 1'b0; B = 1'b0; S = 1'b0;
        #5 A = 1'b0; B = 1'b0; S = 1'b1;
        #5 A = 1'b0; B = 1'b1; S = 1'b0;
        #5 A = 1'b0; B = 1'b1; S = 1'b1;
        #5 A = 1'b1; B = 1'b0; S = 1'b0;
        #5 A = 1'b1; B = 1'b0; S = 1'b1;
        #5 A = 1'b1; B = 1'b1; S = 1'b0;
        #5 A = 1'b1; B = 1'b1; S = 1'b1;

    end
    initial
    begin
        $monitor($time,"A=%b, B=%b, S=%b, X=%b", A,B,S,X);
    end
    initial
    begin
        $dumpfile("mux21.vcd");
        $dumpvars(0, mux21tb);
    end
endmodule
