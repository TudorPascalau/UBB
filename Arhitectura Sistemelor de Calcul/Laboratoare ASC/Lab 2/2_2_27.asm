bits 32

global start        

extern exit               
import exit msvcrt.dll    

; Adunari si scader - a+b-(c+d)+100h

segment data use32 class=data
    ; a,b,c,d - word
    
    a dw 300
    b dw 50
    c dw 200
    d dw 70


segment code use32 class=code
    start:
    
        mov AX, [a] ; AX = a = 300
        add AX, [b] ; AX = a+b = 350
        
        mov BX, [c] ; BX = c = 200
        add BX, [d] ; BX = c+d = 270
        
        sub AX, BX ; AX = a+b-(c+d) = 80
        
        add AX, 100h ; AX = a+b-(c+d)+100h = 80 + 256 = 336
        
        push    dword 0      
        call    [exit]       
