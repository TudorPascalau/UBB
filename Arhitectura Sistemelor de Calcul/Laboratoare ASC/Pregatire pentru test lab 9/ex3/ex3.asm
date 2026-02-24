bits 32

global start        

extern exit, scanf, fopen, fprintf, fclose  
import exit msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll    

; Se da un sir de caractere care contine mai multe cuvinte separate prin spatiu (inclusiv ultimul caracter din sir este spatiu)
; Programul va crea pentru fiecare cuvant din sir un nou fisier care va contine nimarul de caractere din cuvant si care va avea ca nume cuvantul respectiv.

; Varianta sir dat in data segment

segment data use32 class=data
    
    sir db "Ana are mere "
    len_sir equ $-sir
    cuvant times 30 db 0
    
    nume_fisier times 40 db 0
    mod_acces db "w", 0
    descriptor dd -1
    
    format_nr db "%d", 0
    

segment code use32 class=code

    final_cuv:
    
        mov al, 0 ; adaugam terminator
        stosb ; terminam cuvantul cu 0
        
        cmp ebx, 0
        je skip_file
        
        push ecx ; salvam ecx - apeluri C modifica
        push esi ; salvam parcurgerea sirului
        
        cld ; copiem cuvantul in nume_fisier
        mov esi, cuvant
        mov edi, nume_fisier
        
        copiaza_cuvant:
            lodsb
            stosb
            cmp al, 0
            jne copiaza_cuvant
            
        ;am copiat inclusiv 0 terminal , il inlocuim cu .txt
            
        dec edi
        mov al, '.'
        stosb
        mov al, 't'
        stosb
        mov al, 'x'
        stosb
        mov al, 't'
        stosb
        mov al, 0 ; terminatorul
        stosb
        
        ; deschidem fisierul
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        mov [descriptor], eax ; salvam descriptor 
        cmp eax, 0 ; verificam deschiderea
        je skip_file
        
        push ebx ; scriem numarul
        push dword format_nr
        push dword [descriptor]
        call [fprintf]
        add esp, 4*3
        
        push dword [descriptor] ; inchidem fisierul
        call [fclose]
        add esp, 4

        skip_file:
        pop esi ; revenim la esi pt parcurgere sir initial
        
        pop ecx ; restauram ecx
        cmp ecx, 0
        je final
        
        jmp urmator ; citim urmatorul cuvant
        
    start:
    
        cld ; pregatim parcurgerea sirului
        mov ecx, len_sir
        mov esi, sir
        jecxz final
        
        urmator:
            mov ebx, 0 ; numar litere cuvant
            mov edi, cuvant ; pregatim noul cuvant
        
        repeta:
            lodsb ; citim caracterul curent
            cmp al, ' ' ; spatiu = sfarsit cuvant
            je final_cuv
            
            stosb ; nu e spatiu - il adaugam in sir
            inc ebx
            loop repeta
            
        
        final:
        
        push    dword 0      
        call    [exit]       
