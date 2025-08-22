.data
A: .word 0x4500faf3
.text
LDR R0,=A
LDR R1,[R0]
MOV R3,#0
loop: AND R2,R1,#0xf
CMP R2,#9
ADDMI R3,R3,R2
LSR R1,R1,#4
CMP R1,#0
BNE loop
.end