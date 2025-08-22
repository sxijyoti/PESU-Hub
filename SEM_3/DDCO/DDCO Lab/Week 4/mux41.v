module mux21(input wire i0,i1,j, output wire o);
assign o = (j==0)? i0 : i1 ;
endmodule

module mux41(input wire [0:3]i,input wire j0,j1, output wire o);
wire t0,t1;
mux21 mux1(i[0],i[1],j1,t0);
mux21 mux2(i[2],i[3],j1,t1);
mux21 mux3(t0,t1,j0,o);

endmodule
