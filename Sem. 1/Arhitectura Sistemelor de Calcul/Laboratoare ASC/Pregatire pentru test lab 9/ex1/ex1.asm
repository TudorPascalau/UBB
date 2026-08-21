bits 32

global start        

extern exit, printf, fopen, fread, fclose
import exit msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll

; Se dau doua siruri de caractere, S1 de maximum 100 de caractere salvat in fisierul "in.txt" si S2 definit in segmentul de date. 
; Sa se construiasca si sa se afiseze pe ecran sirul D ce contine toate elementele din S1 care nu apar in S2.

segment data use32 class=data

    s1 resb 100
    len1 dd -1
    s2 db 'a','4','5'
    len2 equ $-s2
    
    d resb 100
    
    nume_fisier db "in.txt", 0
    mod_acces db "r", 0
    descriptor dd -1
    
    format db "%s", 0


segment code use32 class=code
    start:
    
        push dword mod_acces ; deschidem fisierul
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0 ; verificam daca s-a deschis corect
        je final
        mov [descriptor], eax ; salvam descriptorul
        
        push dword [descriptor] ; fisier
        push dword 100 ; 100 elemente
        push dword 1 ; byte - caractere
        push dword s1 ; unde le citim
        call [fread]
        add esp, 4*4
        
        mov [len1], eax ; salvam lungimea sirului
        
        push dword [descriptor] ; inchidem fisierul
        call [fclose]
        add esp, 4
        
        cld
        mov esi, s1
        mov edi, d
        mov ecx, len1
        jecxz final_loop
        
        repeta:
            lodsb
            
            push ecx
            push edi
            
            mov edi, s2
            mov ecx, len2
            
            jecxz final_loop2:
            repeta2:
                scasb
                je apare
                loop repeta2
            
            final_loop2:
                pop edi
                pop ecx
                stosb
                jmp urmatorul
            
            apare:
                pop edi
                pop ecx
                
            urmatorul:
            loop repeta
        
        final_loop:
        mov al, 0
        stosb
        
        push dword d
        push dword format
        call [printf]
        add esp, 4*2
        
        final:
        push    dword 0      
        call    [exit]       
