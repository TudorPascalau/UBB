bits 32

global _prefixAsm

segment data public data use32

segment code public code use32
;int prefixAsm(char *s, char *s, char *s)
_prefixAsm:
        ;Cod intrare
        push ebp
        mov ebp, esp
        
        push edi
        push esi
        push ebx
        push ecx
        
        ;Cod apel
        
        xor ecx, ecx
        cld
        mov esi, [ebp+8]
        mov edi, [ebp+12]
        mov ebx, [ebp+16]
        
        .parcurge:
        lodsb
        scasb
        jne .gata
        
        cmp al, 0
        je .gata
        
        mov [ebx], al
        inc ebx
        inc ecx
        jmp .parcurge
        
        .gata:
        mov byte [ebx], 0
        mov eax, ecx
        
        ;Cod iesire
        
        pop ecx
        pop ebx
        pop esi
        pop edi
        
        mov esp, ebp
        pop ebp
        
        ret