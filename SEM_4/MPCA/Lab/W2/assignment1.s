.text
LDR R0,=A
LDR R2,=Count
LDR R1,[R0]
LDR R4,[R2]
loop: ANDS R3,R1,#1
ADDNE R4,R4,#1
MOV R1,R1,LSR #1
CMP R1,#0
BNE loop
STR R4,[R2]

.data
A: .word 7
Count: .word 0