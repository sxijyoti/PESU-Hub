.data
A:  .asciz "*+545\0"
res: .word 0

.text

    LDR R0, =A
    LDR R9, =res
    BL len

loop:
    SUB R0, R0, #1
    LDRB R1, [R0]
    CMP R1, #0
    BEQ fin

    CMP R1, #'0'
    BGE operand
    BL operator

    B loop

operand:
    SUB R1, R1, #'0'
    STMFD R13!, {R1}
    BX LR

operator:
    LDMFD R13!, {R4, R5}
    CMP R1, #'+'
    ADDEQ R6, R4, R5
    CMP R1, #'-'
    SUBEQ R6, R4, R5
    CMP R1, #'*'
    MULEQ R6, R4, R5
    STMFD R13!, {R6}
    BX LR

len:
    MOV R2, #0
len_loop:
    LDRB R1, [R0, R2]
    CMP R1, #0
    BEQ len_done
    ADD R2, R2, #1
    B len_loop

len_done:
    ADD R0, R0, R2
    BX LR

fin:
    LDMFD R13!, {R6}
    STR R6, [R9]