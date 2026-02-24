;Se citesc de la tastatura un numar natural n si n propozitii care contin cel putin n cuvinte (nu se fac validari).
;Sa se afiseze sirul format prin concatenarea cuvintelor de pe pozitia i din propozitia i, i=1,n (separate prin spatiu).

bits 32

global start
extern .citeste_int

extern exit, scanf, printf  
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll    

segment data use32 class=data
    
    format_string db "%s", 0
    buffer resb 100
    
    sir_rez resb 100
    
    pas_curent dd 0

segment code use32 class=code
    start:
    
        ; citim numarul natural n
        
        call _citeste_int
        ; in eax avem numarul natural n
        
        ; citiri repetate de siruri
        
        mov dword [pas_curent], 0
        mov ecx, eax 
        jecxz .done
        
        cld
        mov edi, sir_rez
        
        .repeta_citire
        
        inc dword [pas_curent]
        
        pushad
        
        push dword buffer
        push dword format_string
        call [scanf]
        add esp, 4*2
        
        popad
        
        mov esi, buffer
        mov ebx, buffer ; inceputul cuvantului curent
        mov edx, 0 ; numaram separatorii
        
            .parse:
            lodsb
            cmp al, '_'
            je .gasit_separator
            jmp .parse
            
            .gasit_separator:
            inc edx
            cmp edx, dword [pas_curent]
            je cuvant_cautat
            jmp .parse
            
            cuvant_cautat:
            lodsb 
        
        loop repeta citire
        
        .done:
        
        push    dword 0      
        call    [exit]       
