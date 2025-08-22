.text
LDR R0,=A
LDR R1,=B
LDR R2,=RES
MOV R3,#9

loop:
    LDR R4,[R0],#4
    LDR R5,[R1],#4
    ADD R6,R4,R5
    STR R6,[R2],#4
    SUB R3,R3,#1
    CMP R3,#0
    BNE loop

.data
A: .word 1,2,3,4,5,6,7,8,9
B: .word 9,8,7,6,5,4,3,2,1
RES: .word 0,0,0,0,0,0,0,0,0
