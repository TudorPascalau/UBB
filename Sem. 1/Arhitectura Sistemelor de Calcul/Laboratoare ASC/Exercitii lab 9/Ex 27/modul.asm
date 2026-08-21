bits 32

global _adaugaPareASM

segment data public data use32

segment code public code use32
; int adaugaPareASM(int *, int *, int)
_adaugaPareASM:
        push ebp
        mov ebp, esp
        
        push edi
        push esi
        push ecx
        push ebx
        
        mov esi, [ebp+8]
        mov edi, [ebp+12]
        mov ecx, [ebp+16]
        mov ebx, 0
        
        .repeta:
        lodsd
        test eax, 1
        jnz .impar
        
        stosd
        inc ebx
        
        .impar:
        loop .repeta
        
        mov eax, ebx
        
        pop ebx
        pop ecx
        pop esi
        pop edi
        
        mov esp, ebp
        pop ebp
        
        ret