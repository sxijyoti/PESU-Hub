.data
A: .word 33,44,68,69,3,32,15,88,45,79
Max: .word 

.text
LDR R0,=A
LDR R1,=Max
MOV R2,#9
LDR R3,[R0],#4
loop: LDR R4,[R0],#4
CMP R4,R3
MOVPL R3,R4
SUB R2,#1
CMP R2,#0
BNE loop
STR R3,[R1]
.end