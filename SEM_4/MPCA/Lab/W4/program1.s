.text
    LDR R9, =A
    LDR R10, =BYTESUM
    MOV R3, #0
    MOV R1, #6

loop:
    LDRB R2, [R9], #1
    ADD R3, R3, R2
    SUBS R1, R1, #1
    BNE loop

    STR R3, [R10]

.data
A: .byte 1,2,3,4,5,6
BYTESUM: .word 0
