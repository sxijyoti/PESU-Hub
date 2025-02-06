.text
LDR R1,=A
LDR R2,=B
LDR R3,[r1]
LDR R4,[r2]
CMP R3,R4
BEQ ad
add R0,R3,R4
SWI 0X011
ad :SUB R0,R3,R4

.data
A: .word 2
B: .word 1
