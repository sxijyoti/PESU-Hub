module fulladder(input wire a, b, cin, output wire sum, cout);
  assign sum = a ^ b ^ cin;  
  assign cout = (a & b) | (b & cin) | (a & cin);  
endmodule

module ripplecarry(input wire [3:0] a, b, input wire cin, output wire [3:0] sum, output wire cout);
  wire [2:0] c;  
  fulladder u0 ( .a(a[0]), .b(b[0]), .cin(cin),  .sum(sum[0]), .cout(c[0]) );  
  fulladder u1 ( .a(a[1]), .b(b[1]), .cin(c[0]), .sum(sum[1]), .cout(c[1]) );  
  fulladder u2 ( .a(a[2]), .b(b[2]), .cin(c[1]), .sum(sum[2]), .cout(c[2]) );  
  fulladder u3 ( .a(a[3]), .b(b[3]), .cin(c[2]), .sum(sum[3]), .cout(cout)  ); 
endmodule


