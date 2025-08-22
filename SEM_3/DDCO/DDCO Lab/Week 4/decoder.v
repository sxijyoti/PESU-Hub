module decoder(input wire a,b, output wire y0,y1,y2,y3);
assign y0=(!a)&(!b);
assign y1=(!a)&b;
assign y2= a&(!b);
assign y3= a&b;
endmodule
