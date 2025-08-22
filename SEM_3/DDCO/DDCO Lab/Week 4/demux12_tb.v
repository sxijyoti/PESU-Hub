module demuxtb;
    reg I,S;
    wire X,Y;
    demux12 dm(.I(I),.S(S),.y0(X),.y1(Y));
    initial
    begin
        S=1'b0; I =1'b0;
        #5 S=1'b0; I =1'b1;
        #5 S=1'b1; I =1'b0;
        #5 S=1'b1; I =1'b1;
    

    end
    initial
    begin
        $monitor($time,"S=%b, I=%b, X=%b, Y=%b", S, I, X, Y);
    end
    initial
    begin
        $dumpfile("demux.vcd");
        $dumpvars(0, demuxtb);
    end
endmodule
