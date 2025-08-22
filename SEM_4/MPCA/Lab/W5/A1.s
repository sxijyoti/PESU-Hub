.data
main_s: .asciz "Hello"
sub_s: .asciz "llo"
true: .asciz "true"
false: .asciz "false"

.text
LDR R0,=main_s
LDR R1,=sub_s
reset:
MOV R2,#0
loop:
LDRB R3,[R0,R2]
LDRB R4,[R1,R2]
CMP R4,#0
BEQ found
CMP R3,#0
BEQ not_found
CMP R3,R4
ADDEQ R2,R2,#1
BEQ loop
ADDNE R0,R0,#1
BNE reset
SWI 0x11

not_found:
LDR R5,=false
MOV R0,R5
SWI 0x02
SWI 0X011

found:
LDR R5,=true
MOV R0,R5
SWI 0x02
SWI 0x11

.end