bits 32

global _sumaNumere

segment data public data use32

segment code public code use32
; int sumaNumere(int, int)

_sumaNumere:
    ; Codul de intrare
    push ebp
    mov ebp, esp
    
    ; Codul de apel
    mov eax, [ebp+8]
    mov ebx, [ebp+12]
    
    add eax, ebx ; calculam suma - valoarea finala in eax
    
    ; Codul de iesire - refacem stackframe
    mov esp, ebp
    pop ebp
    
    ret