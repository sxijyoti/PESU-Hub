module mux21(input wire i0,i1,j, output wire o);
assign o = (j==0)? i0 : i1 ;
endmodule

/* here j is the select line*/

