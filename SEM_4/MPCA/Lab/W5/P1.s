.data
A: .word 1, 2, 3, 4, 5, 6, 7, 8, 9
B: .word 9, 8, 7, 6, 5, 4, 3, 2, 1
C: .word 0, 0, 0, 0, 0, 0, 0, 0, 0

.text
LDR R0,=A
LDR R1,=B
LDR R2,=C
MOV R3,#0
MOV R10,#3
iloop:
MOV R4,#0
jloop:
MOV R8,#0
MOV R9,#0
kloop: 
MLA R5,R3,R10,R8
LDR R6, [R0, R5, LSL #2]
MLA R5,R8,R10,R4
LDR R7, [R1, R5, LSL #2]
MLA R9,R6,R7,R9
ADD R8,R8,#1
CMP R8,R10
BNE kloop
MLA R5,R3,R10,R4
STR R9,[R2,R5,LSL #2]
ADD R4,R4,#1
CMP R4,R10
BNE jloop
ADD R3,R3,#1
CMP R3,R10
BNE iloop
.end