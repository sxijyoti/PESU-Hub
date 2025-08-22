.text
LDR R1,=NUM
MOV R2,#0

find_max:
    CMP R1,#0
    BEQ end_program

    AND R3,R1,#0xF
    CMP R3,R2
    MOVHI R2,R3

    LSR R1,R1,#4
    B find_max

end_program:

.data
NUM: .word 0x17845374
