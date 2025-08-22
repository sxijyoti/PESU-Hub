module half_adder_tb;
    reg a,b;
    wire s,c;
    halfadder add1(.a(a),.b(b),.sum(s),.carry(c));
    initial
    begin
        a = 1'b0; b = 1'b0; 
        #5 a = 1'b0; b = 1'b1;
        #5 a = 1'b1; b = 1'b0; 
        #5 a = 1'b1; b = 1'b1; 
    end
    initial
    begin
        $monitor($time,"a=%b, b=%b, sum=%b, carry=%b", a,b,s,c);
    end
    initial
    begin
        $dumpfile("halfadder.vcd");
        $dumpvars(0, half_adder_tb);
    end
endmodule
