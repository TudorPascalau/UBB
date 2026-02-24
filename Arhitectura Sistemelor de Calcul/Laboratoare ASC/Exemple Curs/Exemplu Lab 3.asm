bits 32

global start        

extern exit               
import exit msvcrt.dll    

; (a+b*c+2/c)/(2+a)+e+x - Interpretare cu semn
segment data use32 class=data
    ; a,b - byte
    ; c - word
    ; e - dword
    ; x - qword 
    
    a db 2
    b db 3
    c dw 5
    e dd 12
    x dq 10
    temp db 0FFh

segment code use32 class=code
    start:
    
        ;(a+b*c+2/c)
        
        ;b*c
        mov al, [b]
        cbw ; AX = b
        imul word [c] ; DX:AX = b*c
        
        push dx
        push ax
        pop ebx ; EBX = b*c
        
        ;2/c
        mov ax, 2
        cbw ; DX:AX = 2
        idiv word [c] ; AX = 2/c
        cwde ; EAX = 2/c
        
        ;a+b*c+2/c
        add ebx, eax ; EBX = b*c+2/c
        
        mov al, [a]
        cbw
        cwde ; EAX = a
        add eax, ebx; EAX = a+b*c+2/c
        
        ;2+a
        mov bl, [a];
        add bl, 2; BL = 2+a
        
        push eax
        mov al, bl; AL = 2+a
        cbw ; AX = 2+a
        mov bx, ax ; BX = 2+a
        
        pop ax
        pop dx ; DX:AX = a+b*c+2/c
        
        idiv bx ; AX = (a+b*c+2/c)/(2+a)
        cwde ; EAX = (a+b*c+2/c)/(2+a)
        add eax, [e]
        cdq ; EDX:EAX = a+b*c+2/c)/(2+a)+e
        
        add eax, dword [x]
        adc edx, dword [x+4] ; Rezultatul in EDX:EAX
        
        push    dword 0      
        call    [exit]       
