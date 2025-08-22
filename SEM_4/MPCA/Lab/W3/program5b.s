.data 
A: .word 1,2,3
B: .word 4,5,6

.text
LDR R0,=A
LDR R1,=B
MOV R2,#3
MOV R6,#0
loop: LDR R3,[R0],#4
LDR R4,[R1],#4
MLA R6,R3,R4,R6
SUBS R2,R2,#1
BNE loop
.end