bits 32

global start        

extern exit, fopen, fread, fclose, printf, scanf      
import exit msvcrt.dll 
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt   

;In fisierul "in.txt" se da un sir de maximum 100 de caractere.
;Sa se citeasca de la tastatura cate un caracter pana la introducerea caracterului '$'.
;Pentru fiecare caracter citit, sa se afiseze pe ecran numarul de aparitii al acestuia in sirul din fisier.

;Ex:
;in.txt: abcabAAbcbb

;a => 2
;b => 5
;z => 0
;* => 0
;A => 2
;$ => sfarsit executie.

segment data use32 class=data
    
    nume_fisier db "in.txt", 0
    mod_acces db "r", 0
    descriptor dd -1
    
    text times 101 db 0
    lung_text dd 0
    len equ 100
    
    n db 0
    format_citire db " %c", 0
    
    format_afisare db "%c: %d", 13, 10, 0

segment code use32 class=code
    start:
    
        push dword mod_acces ; deschidem fisierul
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        mov [descriptor], eax ; salvam descriptor
        cmp eax, 0 ; verificam deschiderea corecta a fisierului
        je final
        
        push dword [descriptor] ; citim sirul dat in in.txt
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4*4
        
        mov [lung_text], eax ; cate caractere s-au citit defapt
        cmp eax, 0 ; daca nu s-au citit caractere putem incheia executia
        je final
        
        push dword [descriptor] ; inchidem fisierul
        call [fclose]
        add esp, 4
        
        citire:
            push dword n ; citim caracter
            push dword format_citire
            call [scanf]
            add esp, 4*2
            
            cmp byte [n], '$' ; citim pana la $
            je gata_citire
            
            mov ebx, 0 ; in ebx contorizam numarul de aparitii
            mov eax, 0
            mov al, byte [n] ; in eax avem caracterul
            push eax ; lodsb va modifica
            
            cld ; pregatim loopul
            mov esi, text
            mov ecx, [lung_text]
            jecxz final
            
            repeta: ; comparam caracter cu caracter
                lodsb ; al = caracter din text
                cmp al, byte [n]; comparam caracterul citit cu caracterele din text
                jne ne_egal
                
                inc ebx ; incrementam contorul daca sunt egale
                
                ne_egal:
                loop repeta
                
            pop eax ; revenim la caracterul initial
                
            push ebx ; afisam caracterul si de cate ori apare
            push eax ; afisam caracterul
            push dword format_afisare
            call [printf]
            add esp, 4*3
            
            jmp citire ; reluam citirea pana dam de $
        
        gata_citire:
        
        final:
        push    dword 0      
        call    [exit]       
