.data 
A: .word 23,14,37,28,30,57,12,96,63,69
B: .word 60
.text
LDR R0,=A
LDR R1,=B
LDR R3,[R1]
MOV R5,#10
loop: LDR R2,[R0],#4
SUB R5,R5,#1
CMP R5,#-1
BEQ exit
CMP R2,R3
BNE loop
MOV R4,#1
SWI 0x011

exit: MOV R4,#0
SWI 0x011