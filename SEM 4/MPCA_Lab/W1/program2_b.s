.text
LDR R0,=A
LDR R1,=B
LDR R2,[r0]
LDR R3,[r1]
RSBS R4,R2,R3


.data
A: .word 0xffffffff
B: .word 0