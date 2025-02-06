.text
LDR R0,=A
LDR R6,=esum
LDR R5,[R6]
MOV R2,#6
loop: 
LDR R1,[R0],#4
ANDS R3,R1,#1
ADDEQ R5,R1,R5
SUB R2,#1
CMP R2,#0
BNE loop
STR R5,[R6]



.data
A: .word 10,23,42,35,38,44
esum: .word 0