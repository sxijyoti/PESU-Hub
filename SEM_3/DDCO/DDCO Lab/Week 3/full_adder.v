module halfadder(a,b,sum,carry);
    input a,b;
    output sum, carry;
    assign sum = a^b;
    assign carry= a&b;
endmodule

module fulladder(a,b,cin,sum,cout);
    input a,b,cin;
    output sum,cout;
    wire s1,c1,c2;

    halfadder HA1(.a(a),.b(b),.sum(s1),.carry(c1));
    halfadder HA2(.a(s1),.b(cin),.sum(sum),.carry(c2));

    assign cout=c1|c2;
endmodule

