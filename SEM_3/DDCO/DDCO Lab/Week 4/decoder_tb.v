module decodertb;
    reg a,b;
    wire y0,y1,y2,y3;
    decoder d1(.y0(y0),.y1(y1),.y2(y2),.y3(y3),.a(a),.b(b));
    initial
    begin
        a=1'b0; b=1'b0;
        #5 a=1'b0; b=1'b1;
        #5 a=1'b1; b=1'b0;
        #5 a=1'b1; b=1'b1;
    
    end
    initial
    begin
        $monitor($time," a=%b, b=%b, y0=%b, y1=%b, y2=%b, y3=%b", a,b,y0,y1,y2,y3);
    end
    initial
    begin
        $dumpfile("decoder.vcd");
        $dumpvars(0, decodertb);
    end
endmodule
