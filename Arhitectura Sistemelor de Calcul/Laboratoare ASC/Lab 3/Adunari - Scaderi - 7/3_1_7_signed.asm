bits 32

global start        

extern exit               
import exit msvcrt.dll    

; (c+c+c)-b + (d-a) - Interpretare cu semn
segment data use32 class=data
    ;a - byte
    ;b - word
    ;c - dword
    ;d - qword
    
    a db -10
    b dw 5
    c dd -2
    d dq -20

segment code use32 class=code
    start:
    
        ;d-a        
        mov ebx, dword [d]
        mov ecx, dword [d+4]; ECX:EBX = d (-20)
        
        mov al, [a]
        cbw
        cwde
        cdq ; EDX:EAX = a (-10)
        
        sub ebx, eax
        sbb ecx, edx; ECX:EBX = d-a =(-10)
    
        ; c+c+c
        mov edx, [c]
        add edx, [c]
        add edx, [c] ;EDX = c+c+c (-6)
        
        ;(c+c+c)-b
        mov ax, [b]
        cwde ; EAX = AX = b (=5)
        sub edx, eax ; EDX = (c+c+c)-b (-11)
        
        ;(c+c+c)-b + (d-a)
        mov eax, edx
        cdq ; EDX:EAX = (c+c+c)-b (-11)
        
        add eax, ebx
        adc edx, ecx ; EDX:EAX = (c+c+c)-b + (d-a) (-21)
        
        push    dword 0      
        call    [exit]       
