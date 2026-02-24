bits 32

global _reprezentareHexaAsm
extern _a
extern _printf

segment data public data use32

    format db "%x", 0

segment code public code use32
; reprezentareHexaAsm(int a);
_reprezentareHexaAsm:
        ;Codul de intrare
        push ebp
        mov ebp, esp
        
        ;Codul de apel
        mov eax, [ebp+8] ; parametrul functiei
        push eax
        push format
        call _printf
        add esp, 4*2 ; golim stiva
        
        ;Codul de iesire
        mov esp, ebp
        pop ebp
        
        ret