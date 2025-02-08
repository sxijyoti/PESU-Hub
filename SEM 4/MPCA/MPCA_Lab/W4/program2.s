.text
    LDR R9, =MATRIX  
    MOV R1, #0      

row_loop:
    CMP R1, #4        
    BEQ end_program
    MOV R4, #0        

col_loop:
    CMP R4, #4       
    BEQ next_row

    LSL R5, R1, #2   
    ADD R5, R5, R4    
    LSL R5, R5, #2    
    ADD R6, R9, R5    

    CMP R1, R4        
    MOVEQ R10, #5     
    MOVNE R10, #0     
    STR R10, [R6]     

    ADD R4, R4, #1   
    B col_loop

next_row:
    ADD R1, R1, #1   
    B row_loop

end_program:

.data
MATRIX: .word 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16  
