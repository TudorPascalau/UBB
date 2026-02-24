bits 32

global start        

extern exit, fopen, fread, fclose, printf      
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt

; Se da un fisier text input.txt, care contine un sir de caractere
; Sa se determine si sa se afiseze pe ecran numarul de aparitii al fiecarui litere din fisier
; Literele mari si mici se vor considera la fel (nu se face diferenta intre majuscule)
; Se vor afisa doar literele care apar in text, impreuna cu numarul lor de aparitii    

segment data use32 class=data
    
    nume_fisier db "input.txt", 0
    mod_acces db "r", 0
    descriptor dd -1
    
    frecv times 200 db 0
    
    len equ 100
    text times (len+1) db 0
    len_text dd 0
    
    format_afisare db "%c: %d", 13, 10, 0

segment code use32 class=code
    start:
    
        push dword mod_acces ; deschidem fisierul
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        mov [descriptor], eax ; salvam descriptorul
        cmp eax, 0 ; verificam deschiderea fisierului
        je final
        
        push dword [descriptor] ; citim textul
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4*4
        
        mov [len_text], eax ; salvam lungimea reala a sirului
        
        cld ; pregatim parcurgerea sirului
        mov esi, text
        mov ecx, [len_text]
        jecxz final
        
        repeta: ; contorizam toate literele din text
            xor eax, eax
            lodsb ; eax = valoarea literei
            
            cmp eax, 'A'
            jb skip_caracter
            cmp eax, 'Z'
            jbe litera_mare
            
            cmp eax, 'a'
            jb skip_caracter
            cmp eax, 'z'
            ja skip_caracter
            
            sub eax, 'a'
            jmp contorizare
            
            litera_mare:
            sub eax, 'A'
            
            contorizare:
            inc byte[frecv+eax] ; frecv[litera]++, unde frecv[0] reprezinta frecv[a]
            
            skip_caracter:
            loop repeta
            
        cld
        mov esi, frecv
        mov ebx, 'a'
        mov ecx, 26
        afisari_litere:
            push ecx ; salvame ecx / apeluri modifica
            
            mov eax, 0
            lodsb ; eax = numarul de aparitii al literei
            
            cmp eax, 0
            je skip_afisare
            
            push eax
            push ebx
            push format_afisare
            call [printf]
            add esp, 4*3
            
            skip_afisare:
            inc ebx
            pop ecx
            loop afisari_litere
        
        final:
        
        push dword [descriptor]
        call [fclose]
        add esp, 4
        
        push    dword 0      
        call    [exit]       
