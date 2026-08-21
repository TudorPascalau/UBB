bits 32

global start        

extern exit               
import exit msvcrt.dll    

; ((a+b+c)*2 + d-5)*d

segment data use32 class=data
    ; a,b,c - byte
    ; d - word
    
    a db 10
    b db 20
    c db 15
    d dw 30


segment code use32 class=code
    start:
    
        mov AH, [a] ; AH = a = 10
        add AH, [b] ; AH = a+b = 30
        add AH, [c] ; AH = a+b+c = 45
        
        mov AL, 2 ; AH = 2
        mul AH ; AX = AL * AH = (a+b+c+)*2 = 90
        
        add AX, [d] ; AX = (a+b+c)*2 + d = 120
        sub AX, 5; AX = (a+b+c)*2 + d-5 = 115
        
        mul word [d] ; DX:AX = AX * WORD [d] = 115*30 = 3450
        
        push    dword 0      
        call    [exit]       
