.data
A: .word 56
B: .word 4

.text
LDR R0,=A
LDR R1,=B
LDR R2,[R0]
LDR R3,[R1]
loop: SUBS R2,R2,R3
BPL loop
ADD R2,R2,R3