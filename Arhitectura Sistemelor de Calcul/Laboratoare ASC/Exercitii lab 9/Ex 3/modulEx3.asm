bits 32

global _concatenareAsm

segment data public data use32

segment code public code use32
;void concatenareAsm(char *, char *, char *)
_concatenareAsm:
        
        ;Codul de intrare
        push ebp
        mov ebp, esp
        push esi
        push edi
        
        ;Codul de apel
        
        ;concatenam cifre zecimale din primul sir
        mov esi, [ebp+8]
        mov edi, [ebp+16]
        cld
        
        .parcurge_primul:
        lodsb
        
        cmp al, 0
        je .gata_primul
        
        cmp al, '0'
        jb .parcurge_primul
        
        cmp al, '9'
        ja .parcurge_primul
        
        stosb
        jmp .parcurge_primul
        
        .gata_primul:
        
        ;concatenam cifrele zecimale din al doilea sir
        mov esi, [ebp+12]
        
        .parcurge_doi:
        
        lodsb
        
        cmp al, 0
        je .gata_doi
        
        cmp al, '0'
        jb .parcurge_doi
        
        cmp al, '9'
        ja .parcurge_doi
        
        stosb
        jmp .parcurge_doi
        
        .gata_doi:
        
        ;punem terminatorul \0
        mov al, 0
        stosb
        
        ;Codul de iesire
        pop edi
        pop esi
        mov esp, ebp
        pop ebp ;leave
        
        ret