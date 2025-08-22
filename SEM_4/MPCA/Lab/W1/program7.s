.text
MOV R0, #50
MOV R1, #75
loop: cmp R0, R1
BLMI neg
BEQ fin
SUBS R0,R0,R1
BNE loop

neg: MOV R2,R0
MOV R0,R1
MOV R1,R2
BX lr

fin: .end