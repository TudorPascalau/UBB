bits 32

extern _printf
global _hello_world   

segment data public data use32
    
    mesaj db "Hello world!", 0

segment code public code use32
_hello_world:
        ; Codul de intrare
        push ebp
        mov ebp, esp
        
        ;Codul de apel
        push dword mesaj
        call _printf
        add esp, 4*1
        
        ; Codul de iesire
        pop ebp
        
    ret