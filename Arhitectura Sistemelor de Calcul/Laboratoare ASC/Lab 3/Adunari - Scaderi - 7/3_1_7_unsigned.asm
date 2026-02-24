bits 32

global start        

extern exit               
import exit msvcrt.dll    

; c - (d+d+d) + (a-b) - Interpretare fara semn


segment data use32 class=data
    ; a - byte
    ; b - word
    ; c - dword
    ; d - qword
    
    a db 10
    b dw 5
    c dd 20
    d dq 4


segment code use32 class=code
    start:
    
        ; c
        mov eax, [c]
        mov edx, 0 ; EDX:EAX = c (=20)
        
        ; d+d+d
        mov ebx, dword [d]
        mov ecx, dword [d+4] ; ECX:EBX = d (=4)
        
        add ebx, [d]
        adc ecx, [d+4]
        
        add ebx, [d]
        adc ecx, [d+4] ; ECX:EBX = d+d+d (=12)
        
        ; c - (d+d+d)
        sub eax, ebx
        sbb edx, ecx ; EDX:EAX = c - (d+d+d) (=8)
        
        ; a-b
        mov ebx, 0
        mov bl, [a]
        mov bh, 0 ; BX = a (=10)
        sub bx, [b]; EBX = BX = a-b (5)

        ;c - (d+d+d) + (a-b)
        add eax, ebx
        adc edx, 0 ;EDX:EAX = c - (d+d+d) + (a-b) (=13)
        
        push    dword 0      
        call    [exit]       
