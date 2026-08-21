bits 32

global start        

extern exit, scanf, fopen, fprintf, fclose  
import exit msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

; Sa se citeasca cifre de la tastatura pana la intalnirea caracterului $
; Sa sa se scrie intr-un fisier fiecare cifra para si apoi numarul cel mai mic posibil format din exact trei cifre pare din cele citite (daca exita)
; Daca nu exista 3 cifre pare, atunci fisierul va contine doar cifrele pare existente (poate fi si vid)    

segment data use32 class=data
    
    n db 0
    format_citire db "%c", 0
    
    nume_fisier db "numar.txt", 0
    mod_acces db "w", 0
    descriptor dd 0
    
    format_numar db "%d", 0
    format_spatiu db "%c", 0
    
    x db 10 ; unde tinem minte cifrele mici
    y db 10
    z db 10

segment code use32 class=code
    start:
    
        
        
        mov edi, 0 ; contor numere pare
    
        push dword mod_acces ; deschidem fisierul
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        mov [descriptor], eax ; salvam descriptor
        cmp eax, 0
        je final
    
        citeste:
            push dword n ; citim cifre
            push dword format_citire
            call [scanf]
            add esp, 4*2
            
            mov eax, 0
            mov al, [n] ; salvam in eax pt lucru mai usor
            cmp al, '$' ; pana dam de $
            je gata_citire
            
            cmp al, ' ' ; sarim peste spatii
            je citeste
            
            sub al, '0' ; transformam val ASCII in val cifrei
            
            test al, 1
            jnz nu_e_par
            
            inc edi ; contorizam numarul de cifre pare
            
            cmp al, [x]; deoarece valoare citita este doar o cifra, se ia in considerare doar partea low
            jae al_doilea_mic
            
            mov [x], al
            jmp dupa_comparari
            
            al_doilea_mic:
            cmp al, [y]
            jae al_treilea_mic
            
            mov [y], al
            jmp dupa_comparari
            
            al_treilea_mic:
            cmp al, [z]
            jae dupa_comparari
            
            mov [z], al
            
            dupa_comparari:
            
            push eax
            push dword format_numar
            push dword [descriptor]
            call [fprintf]
            add esp, 4*3
            
            mov eax, ' '
            push eax
            push dword format_spatiu
            push dword [descriptor]
            call [fprintf]
            add esp, 4*3
            
            nu_e_par:
            
            jmp citeste ; reluam citirea
            
        gata_citire:
        
        cmp edi, 3
        jb skip_numar
        
        mov eax, 0 ; prima cifra
        mov al, [x]
        
        push eax
        push dword format_numar
        push dword [descriptor]
        call [fprintf]
        add esp, 4*3
        
        mov eax, 0 ; a doua cifra
        mov al, [y]
        
        push eax
        push dword format_numar
        push dword [descriptor]
        call [fprintf]
        add esp, 4*3
        
        mov eax, 0 ; a treia cifra
        mov al, [z]
        
        push eax
        push dword format_numar
        push dword [descriptor]
        call [fprintf]
        add esp, 4*3
        
        skip_numar:
        
        push dword [descriptor]
        call [fclose]
        add esp, 4
        
        final:
        
        push    dword 0      
        call    [exit]       
