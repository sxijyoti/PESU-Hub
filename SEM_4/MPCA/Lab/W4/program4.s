.text
    LDR R9, =A          
    LDR R3, =X          
    LDR R4, =Y          
    LDR R3, [R3]        
    LDR R4, [R4]        
    MOV R1, #3         
    MOV R2, #4          

    
    MLA R5, R4, R1, R3  

    LSL R6, R5, #2      
    ADD R6, R6, R9     

.data
A:  .word 1,2,3,4,5,6,7,8,9 
X:  .word 0   
Y:  .word 1   
