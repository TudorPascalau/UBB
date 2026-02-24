bits 32

global _factorial    

segment data public data use32
    

segment code public code use32
_factorial:
        ;Codul de intrare
        push ebp
        mov ebp, esp
        sub esp, 4 ; Pregatim un dword
        ; [ebp+8] = argument functie = n
        ; [ebp-4] = variabila locala = m
        
        ;Codul de apel
        mov eax, [ebp+8] ; n
        cmp eax, 1
        jbe .trivial
        
        .recursiv:
            dec eax ; eax = n - 1
            push eax
            call _factorial
            add esp, 4 ; curatam stiva
            
            mov [ebp-4], eax ; m = (n-1)!
            mov eax, [ebp+8] ; n
            mul dword [ebp-4]; edx:eax = n*m = n*(n-1)! = n!
            jmp .final
        
        .trivial:
            mov eax, 1
            xor edx, edx
            
        .final:
            
        ;Codul de iesire
        add esp, 4
        mov esp, ebp
        pop ebp
    ret