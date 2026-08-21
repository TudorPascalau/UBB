bits 32

global _concatenareASM

segment data public data use32

segment code public code use32
; concatenareASM(char *sursa, char *rez)

_concatenareASM:
        push ebp
        mov ebp, esp
        
        push esi
        push edi
        
        mov esi, [ebp+8]
        mov edi, [ebp+12]
        
        .gaseste_final:
        cmp byte [edi], 0
        je .concatenare
        inc edi
        jmp .gaseste_final
        
        .concatenare:
        lodsb
        cmp al, '_'
        je .done
        cmp al, 0
        je .done
        cmp al, 10
        je .done
        cmp al, 13
        je .done
        
        stosb
        jmp .concatenare
        
        .done:
        mov al, ' '
        stosb
        mov al, 0
        stosb
        
        pop edi
        pop esi
        
        mov esp, ebp
        pop ebp
        
        ret