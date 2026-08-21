bits 32

extern descriptor, format_citire, numar
extern fscanf

segment code use32 class=code

global citeste

citeste:
    ; fscanf(stream, format, locale)
    push dword numar
    push dword format_citire
    push dword [descriptor]
    
    call [fscanf] ; eax indica daca am citit corect
    add esp, 4*3
    
    ret ; nu avem parametri pasati la procedura