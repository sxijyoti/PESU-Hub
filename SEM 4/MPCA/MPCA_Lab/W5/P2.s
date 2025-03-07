.data
s: .asciz "Hello"

.text
LDR R0,=s
MOV R1,#0
loop:
LDRB R2,[R0],#1
CMP R2,#0
ADDNE R1,R1,#1
BNE loop
.end