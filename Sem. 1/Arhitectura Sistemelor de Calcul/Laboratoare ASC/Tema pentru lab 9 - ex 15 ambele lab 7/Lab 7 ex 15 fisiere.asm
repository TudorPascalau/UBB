bits 32

global start        

extern exit, fopen, fprintf, fclose  
import exit msvcrt.dll  
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll  

; Se dau un nume de fisier si un text (definite in segmentul de date). Textul contine litere mici, litere mari, cifre si caractere speciale. 
; Sa se inlocuiasca toate caracterele speciale din textul dat cu caracterul 'X'. 
; Sa se creeze un fisier cu numele dat si sa se scrie textul obtinut in fisier.

segment data use32 class=data
    
        nume_fisier db "lab 7 ex 15.txt", 0
        mod_acces db "w", 0
        
        text db "Textul contine litere mici! mari 1 cifra & caractere speciale?"
        len equ $-text
        
        rezultat times len+1 db 0
        
        descriptor dd -1

segment code use32 class=code
    start:
    
        push dword mod_acces ; deschidem fisierul
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        mov [descriptor], eax ; tinem minte descriptorul
        
        cmp eax, 0 ; verificam daca functia fopen a deschis cu succes fisierul
        je final
        
        mov esi, text
        mov edi, rezultat
        mov ecx, len
        cld
        
        jecxz skip
        
        repeta:
            lodsb ; al = caracter din sir
            cmp al, 'A' ; verificam daca caracterul este special
            jae nespecial
            
            cmp al, '0'
            jb special
            
            cmp al, '9'
            ja special
            
            special:
            mov al, "X"
            
            nespecial:
            stosb
            
            loop repeta
            
        skip:
            
        push dword rezultat ; scriem in fisier rezultatul
        push dword [descriptor]
        call [fprintf]
        add esp, 4*2
        
        push dword [descriptor] ; inchidem fisierul
        call [fclose]
        add esp, 4*1
        
        final:
        push    dword 0      
        call    [exit]       
