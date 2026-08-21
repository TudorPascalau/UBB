bits 32

global start        

extern exit               
import exit msvcrt.dll    

; Rezolvari si scaderi - (b+b) + (c-a) + d

segment data use32 class=data
    
    ; a,b,c,d - byte
    a db 10
    b db 20
    c db 15
    d db 5


segment code use32 class=code
    start:
    
        mov AL, [b] ; AL = b = 20
        add AL, [b] ; AL = (b+b) = 40
        
        mov BL, [c] ; BL = c = 15
        sub BL, [a] ; BL = (c-a) = 5
        
        add AL, BL ; AL = AL - BL = (b+b) + (c-a) = 45
        
        add AL, [d] ; AL = (b+b) + (c-a) + d = 50
        
        push    dword 0      
        call    [exit]       
