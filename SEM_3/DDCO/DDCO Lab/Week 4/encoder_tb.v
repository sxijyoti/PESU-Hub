module encodertb;
    reg y0,y1,y2,y3;
    wire a0,a1;
    encoder e1(.y0(y0),.y1(y1),.y2(y2),.y3(y3),.a1(a1),.a0(a0));
    initial
    begin
            y0=1'b1; y1=1'b0; y2=1'b0; y3=1'b0;
            #5 y0=1'b0; y1=1'b1; y2=1'b0; y3=1'b0;
            #5 y0=1'b0; y1=1'b0; y2=1'b1; y3=1'b0;
            #5 y0=1'b0; y1=1'b0; y2=1'b0; y3=1'b1;

    end
    initial
    begin
        $monitor($time,"y0=%b, y1=%b, y2=%b, y3=%b, a1=%b, a0=%b", y0,y1,y2,y3,a1,a0);
    end
    initial
    begin
        $dumpfile("encode.vcd");
        $dumpvars(0, encodertb);
    end
endmodule
