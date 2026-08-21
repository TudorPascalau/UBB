bits 32

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    


segment code use32 class=code
    start:
    
        mov BX, 256
        mov AL, 1
        mul BX
        
        push    dword 0      
        call    [exit]       
