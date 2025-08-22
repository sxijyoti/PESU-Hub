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

module circuit_3(A2, B2, C2, Z);
    input A2, B2, C2;
    output Z;
    wire w1, w2, w3;

    andgate G1(.y(w1), .a(C2), .b(B2));
    orgate G2(.y(w2), .a(A2), .b(w1));
    andgate G3(.y(w3), .a(A2), .b(B2));
    orgate G4(.y(Z), .a(w2), .b(w3));
endmodule
