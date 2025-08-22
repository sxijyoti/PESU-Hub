module encoder(input wire y0,y1,y2,y3, output wire a0, a1);
assign a1=y2+y3;
assign a0=y1+y3;
endmodule
