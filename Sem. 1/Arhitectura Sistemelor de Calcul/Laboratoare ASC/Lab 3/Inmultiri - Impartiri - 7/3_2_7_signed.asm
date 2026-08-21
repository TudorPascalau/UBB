bits 32

global start        

extern exit               
import exit msvcrt.dll    

; (a-2)/(b+c)+a*c+e-x - Interpretare cu semn
segment data use32 class=data
    ; a,b-byte
    ; c-word
    ; e-doubleword
    ; x-qword
    
    a db 8
    b db -2
    c dw -1
    e dd -5
    x dq 10


segment code use32 class=code
    start:
    
        ;b+c
        mov al, [b]
        cbw ; AX = b
        add ax, [c]; AX = b+c (= -3)
        
        ;stocare
        mov bx, ax ; BX = b+c (= -3)
        
        ;(a-2)/(b+c)
        mov al, [a]
        sub al, 2
        cbw
        cwd ; DX:AX = a-2 (= 6)
        idiv bx ; AX = DX:AX/BX = (a-2)/(b+c) = (-2)
        
        ;stocare
        mov bx,ax ; BX = (a-2)/(b+c) (= -2)
        
        ;a*c
        mov al, [a]
        cbw ; AX = a (= 8)
        imul word [c]; DX:AX = AX*c = a*c (=-8)
        
        ;stocare
        push dx
        push ax
        pop ecx; ECX = a*c (= -8)
        
        ;(a-2)/(b+c)+a*c
        mov ax, bx
        cwde ; EAX = (a-2)/(b+c) (= -2)
        add eax, ecx; EAX = ;(a-2)/(b+c)+a*c (= -10)
        
        ;(a-2)/(b+c)+a*c+e
        add eax, [e] ; EAX = (a-2)/(b+c)+a*c+e (= -15)
        
        ;(a-2)/(b+c)+a*c+e-x
        cdq ; EDX:EAX = (a-2)/(b+c)+a*c+e
        sub eax, [x]
        sbb edx, [x+4] ; EDX:EAX = (a-2)/(b+c)+a*c+e-x (= -25)
        
        push    dword 0      
        call    [exit]       
