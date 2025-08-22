.text
    LDR R0, =A          
    LDR R1, =B          
    MOV R2, #10         
    ADD R3, R0, #36     

reverse_loop:
    CMP R2, #0          
    BEQ end_program

    LDR R4, [R3], #-4   
    STR R4, [R1], #4    

    SUB R2, R2, #1      
    B reverse_loop

end_program:

.data
A: .word 1,2,3,4,5,6,7,8,9,10  
B: .word 0,0,0,0,0,0,0,0,0,0    
