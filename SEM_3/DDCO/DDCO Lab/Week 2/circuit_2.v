module andgate(y, a, b);
    input a, b;
    output y;
    assign y = a & b;
endmodule

module orgate(y, a, b);
    input a, b;
    output y;
    assign y = a | b;
endmodule

module circuit_2(A, B, C, D);
    input A, B, C;
    output D;
    wire w1;

    andgate G1(.y(w1), .a(C), .b(B));
    orgate G3(.y(D), .a(w1), .b(A));
endmodule
