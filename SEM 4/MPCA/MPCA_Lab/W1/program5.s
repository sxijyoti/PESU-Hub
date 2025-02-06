.text
LDR R0,=A
LDR R1,=B
LDR R2,[r0]
LDR R3,[r1]
AND R4,R2,R3


.data
A: .word 3
B: .word 1