module full_adder_tb;
    reg a,b,ci;
    wire s,co;
    fulladder full1(.a(a),.b(b),.cin(ci),.sum(s),.cout(co));
    initial
    begin
        a = 1'b0; b = 1'b0;ci=1'b0;
        #5  a = 1'b0;b = 1'b0;ci=1'b1;
        #5  a = 1'b0;b = 1'b1;ci=1'b0;
        #5  a = 1'b0;b = 1'b1;ci=1'b1;
        #5  a = 1'b1;b = 1'b0;ci=1'b0;
        #5  a = 1'b1;b = 1'b0;ci=1'b1;
        #5  a = 1'b1;b = 1'b1;ci=1'b0;
        #5  a = 1'b1;b = 1'b1;ci=1'b1;
 
    end
    initial
    begin
        $monitor($time,"a=%b, b=%b, cin=%b, sum=%b, cout=%b", a,b,ci,s,co);
    end
    initial
    begin
        $dumpfile("fulladder.vcd");
        $dumpvars(0, full_adder_tb);
    end
endmodule
