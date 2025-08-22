.data
s: .asciz "Hello"

.text
LDR R0,=s
SWI 0x02
MOV R3,R0
LDRB R1,[R0]
loop:
LDRB R2,[R0],#1
CMP R2,#0
BNE loop
SUB R0,R0,#2
LDRB R2,[R0]
STRB R2,[R3]
STRB R1,[R0]
LDR R0,=s
SWI 0x02
.end