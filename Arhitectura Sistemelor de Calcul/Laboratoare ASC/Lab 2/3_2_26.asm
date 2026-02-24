bits 32

global start        

extern exit               
import exit msvcrt.dll    

; (e+g-2*b)/c
segment data use32 class=data
    ; b,c - byte
    ; e,g - word
    
    b db 20
    c db 10
    e dw 300
    g dw 40


segment code use32 class=code
    start:
    
        mov AL, 2;
        mul byte [b]; AX = AL * [b] = 2*b = 40
        
        neg AX; AX = -AX = -2*b = 40
        add AX, [g]; AX = g-2*b = 0
        add AX, [e]; AX = e+g-2*b = 300
        
        div byte [c]; AL = AX / c = (e+g-2*b)/c = 10; AH = AX % c = 0
        
        push    dword 0      
        call    [exit]       
