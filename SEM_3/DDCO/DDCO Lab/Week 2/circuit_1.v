module andgate(y, a, b);
    input a, b;
    output y;
    assign y = a & b;
endmodule

module notgate(y, a);
    input a;
    output y;
    assign y = !a;
endmodule

module orgate(y, a, b);
    input a, b;
    output y;
    assign y = a | b;
endmodule

module circuit_1(A, B, C, D, E);
    input A, B, C;
    output D, E;
    wire w1;

    andgate G1(.y(w1), .a(A), .b(B));
    notgate G2(.y(E), .a(C));
    orgate G3(.y(D), .a(w1), .b(E));
endmodule
