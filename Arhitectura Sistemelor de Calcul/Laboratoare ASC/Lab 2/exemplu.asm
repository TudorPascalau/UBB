bits 32

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    


segment code use32 class=code
    start:
        
        mov AX, 300
        mov BX, 256
        add AX, BX
        sub AX, BX
        
        push    dword 0      
        call    [exit]       
