.text
LDR R0,=A
LDR R1,=B
LDR R2,[r0]
LDR R3,[r0, #4]
LDR R4,[r0, #8] 
LDR R5,[r0, #12]
LDR R6,[r1] 
LDR R7,[r1, #4]
LDR R8,[r1, #8] 
LDR R9,[r1, #12]
adds R5,R5,R9
adcs R4,R4,R8
adcs R3,R3,R7
adcs R2,R2,R6

.data
A: .word 0xffff0000,0x0000ffff,0xf0f0f0f0,0x0f0f0f0f
B: .word 0xffffffff,0x00000000,0x00000000,0xffffffff