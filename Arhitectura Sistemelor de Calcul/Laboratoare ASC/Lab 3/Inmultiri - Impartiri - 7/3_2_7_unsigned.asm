bits 32

global start        

extern exit               
import exit msvcrt.dll    

; (a-2)/(b+c)+a*c+e-x - Interpretare fara semn
segment data use32 class=data
    ; a,b-byte
    ; c-word
    ; e-doubleword
    ; x-qword

    a db 22
    b db 4
    c dw 6
    e dd 15
    x dq 30

segment code use32 class=code
    start:
    
        ;b+c-word        
        mov al, [b]
        mov ah, 0 ; AX = b
        mov bx, [c] ; BX = c
        add bx, ax; BX = b+c
        
        ;a-2
        mov al, [a]
        mov ah, 0
        mov dx, 0; DX:AX = a-2
        
        ;(a-2)/(b+c)
        div BX; AX = DX:AX / BX = (a-2)/(b+c)
        
        ;stocare
        mov BX, AX; BX = (a-2)/(b+c)
        
        mov al, [a]
        mov ah, 0; AX = a
        mul word [c]; DX:AX = a*c
        
        ;(a-2)/(b+c)+a*c
        add ax, bx
        adc dx, 0 ; DX:AX = (a-2)/(b+c)+a*c
        
        ;stocare
        push dx
        push ax
        pop eax ; EAX = (a-2)/(b+c)+a*c
        
        ;(a-2)/(b+c)+a*c+e
        add eax, [e] ; EAX = (a-2)/(b+c)+a*c+e
        
        ;(a-2)/(b+c)+a*c+e-x
        mov edx, 0
        sub eax, [x]
        sbb edx, [x+4]; EDX:EAX = (a-2)/(b+c)+a*c+e-x (=)
        
        push    dword 0      
        call    [exit]       
