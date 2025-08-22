module demux12(input wire I,S, output wire y0,y1);
assign y0 = ((!S)&I);
assign y1 = (S&I);
endmodule
