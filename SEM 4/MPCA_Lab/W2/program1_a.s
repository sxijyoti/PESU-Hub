.text
LDR R3,=A
LDR R2,=B
LDR R0,[R3]
MOV R1,R0,LSL #3
ADD R1,R1,R1,LSL #1
STR R1,[R2]

.data
A: .word 16
B: .word