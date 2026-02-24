bits 32

global start        

extern exit, scanf, printf               
import exit msvcrt.dll    
import printf msvcrt.dll
import scanf msvcrt.dll

; Se citesc de la tastatura un numar natural n si n propozitii care contin cel putin n cuvinte (nu se fac validari).
; Sa se afiseze sirul format prin concatenarea cuvintelor de pe pozitia i din propozitia i, i=1,n (separate prin spatiu).

segment data use32 class=data
    n dd 0
    format_citire_n db "%d", 0
    buffer resb 100
    format_citire_prop db "%s", 0
    sir_rez resb 100
    pas_curent dd 0
    pozitie_sir_rez dd 0

segment code use32 class=code
    copiere_cuvant:
        mov esi, [esp+12]
        mov ebx, [esp+8]
        mov edi, [esp+4]
        
        mov ecx, esi
        sub ecx, ebx   ; ECX contine lungimea cuvantului
                
        mov esi, ebx
                
        repeta3:
            movsb
        loop repeta3
        
        mov eax, edi
        ret 3*4
    
    start:
        push dword n
        push dword format_citire_n
        call [scanf]
        add esp, 4*2
        
        mov ecx, [n]
        mov edi, sir_rez
        mov dword [pas_curent], 0
        jecxz final
        repeta:
            ; Citim o propozitie
            pusha
            
            push dword buffer
            push dword format_citire_prop
            call [scanf]
            add esp, 4*2
            
            popa
            
            mov esi, buffer
            mov ebx, buffer  ; Inceputul cuvantului curent
            mov edx, 0     ; Numaram spatiile
            
            repeta2:
                lodsb
                cmp AL, '_'
                je gasit_spatiu
                jmp repeta2
                
                gasit_spatiu:
                cmp edx, [pas_curent]
                je gasit_cuvant_cautat
                jmp alt_spatiu
                
                gasit_cuvant_cautat:
                ; Copiam cuvantul (de la punctul de inceput in EBX)
                ; Determinam lungimea cuvantului
                pusha
                
                push esi
                push ebx
                push edi
                call copiere_cuvant
                mov [pozitie_sir_rez], eax
                
                popa
                mov edi, [pozitie_sir_rez]
                
                jmp final_repeta2
                
                alt_spatiu:
                mov ebx, esi  ; Schimbam locul de inceput al cuvantului curent
                inc edx
            jmp repeta2
            final_repeta2:
            
            inc dword [pas_curent]
        loop repeta
        
        mov AL, 0
        stosb
        
        push dword sir_rez
        push dword format_citire_prop
        call [printf]
        add esp, 4*2
        
        
        final:
        push    dword 0      
        call    [exit]       
