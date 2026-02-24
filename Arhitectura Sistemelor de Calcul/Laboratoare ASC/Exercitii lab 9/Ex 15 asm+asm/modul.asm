bits 32

global _citeste_int

extern scanf
import scanf msvcrt.dll

segment data use32 class=data
    
    format_citire_int db "Introduceti n: %d" , 0
    n dd 0

segment code use32 class=code
    _citeste_int:
        push dword n
        push dword format_citire_int
        call [scanf]
        add esp, 4*2
        
        mov eax, [n]
        
        ret