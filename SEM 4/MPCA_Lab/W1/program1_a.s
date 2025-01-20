.text
LDR R0,=A
LDR R1,=B
LDR R2,=C
LDR R3,=D
LDR R4,[r0]
LDR R5,[r1]
LDR R6,[r2]
LDR R7,[r3]
adds R4,R4,R6
adcs R5,R5,R7

.data
A: .word 0xffff0000
B: .word 0x0000ffff
C: .word 0xffffffff
D: .word 0x00000000