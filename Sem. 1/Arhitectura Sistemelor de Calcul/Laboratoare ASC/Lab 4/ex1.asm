bits 32

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data

;Se dau cuvintele A si B. Sa se obtina dublucuvantul C:
;bitii 0-4 ai lui C coincid cu bitii 11-15 ai lui A
;bitii 5-11 ai lui C au valoarea 1
;bitii 12-15 ai lui C coincid cu bitii 8-11 ai lui B
;bitii 16-31 ai lui C coincid cu bitii lui A

    a dw 0011001010100001b
    b dw 1010111100110100b
    c dd 0
    ; rezultatul final ar trebui sa fie 00110010101000011111111111100110b = 34A1FFE6

segment code use32 class=code
    start:
    
        mov ebx, 0 ; in registrul ebx vom calcula rezultatul
        
        
        mov eax, [a]
        and eax, 1111100000000000b ;izolam bitii 11-15 ai lui a
        mov cl, 11
        ror eax, cl ; rotim 11 pozitii spre dreapta
        or ebx, eax; punem in rezultat
        
        ;facem bitii 5-11 sa aiba valoarea 1
        or ebx, 0000111111100000b
        
        
        mov eax, [b]
        and eax, 0000111100000000b ;izolam bitii 8-11 ai lui b
        mov cl, 4
        rol eax, cl ;rotim 4 pozitii spre stanga
        or ebx, eax ;punem in rezultat
        
        mov eax, [a];bitii lui a
        mov cl, 16
        rol eax, cl ; rotim 16 pozitii la stanga
        or ebx, eax; punem in rezultat
        
        mov [c], ebx
        
        push    dword 0      
        call    [exit]       
