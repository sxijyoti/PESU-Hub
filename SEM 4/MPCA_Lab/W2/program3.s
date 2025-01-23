.data
Array: .word 6,13,16,34,28,59,83,96,17,53
even: .word 0,0,0,0,0,0
odd: .word 0,0,0,0,0,0

.text
LDR R0,=Array
LDR R1,=even
LDR R2,=odd
MOV R6,#10
loop: LDR R3,[R0],#4
ANDS R4,R3,#1
STREQ R3,[R1],#4
STRNE R3,[R2],#4
SUB R6,#1
CMP R6,#0
BNE loop
.end