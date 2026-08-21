bits 32

global start        

extern exit               
import exit msvcrt.dll    

; c+(a*a-b+7)/(2+a) INTREPRETARE CU SEMN

segment data use32 class=data
    ; a - byte
    ; b - dword
    ; c - qword
    
    a db 5
    b dd 2
    c dq 3


segment code use32 class=code
    start:
    
        ; a*a-b+7
        mov AL, [a]
        imul byte [a] ; AX = a*a-b
        
        cwde ; EAX = a*a
        sub EAX, [b]
        add EAX, 7 ; EAX = a*a-b+7
        
        mov ECX, EAX
        
        ; 2+a*a
        mov AL, 2
        add AL, [a] ; AL = 2+a
        
        cbw ; AX = 2+a
        
        mov BX, AX
        ; dword / word -> DX:AX / word
        push ECX
        pop AX
        pop DX 
        
        ; DX:AX = a*a-b+7
        ; BX = 2+a
        
        idiv BX ; AX = (a*a-b+7)/(2+a)
        
        cwde ; EAX = AX
        cdq ; EDX:EAX = EAX = AX = (a*a-b+7)/(2+a)
        
        mov EBX, [c]
        mov ECX, [c+4]
        
        ;adunam EDX:EAX cu ECX:EBX
        
        add EAX,EBX
        adc EDX,ECX
        
        ;Rezultatul in EDX:EAX = c+(a*a-b+7)/(2+a) INTREPRETARE CU SEMN
        
        push    dword 0      
        call    [exit]       
