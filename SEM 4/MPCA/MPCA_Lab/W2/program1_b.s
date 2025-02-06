.text
LDR R3,=A
LDR R2,=B
LDR R0,[R3]
MOV R1,R0,LSL #4
STR R1,[R2]

.data
A: .word 24
B: .word