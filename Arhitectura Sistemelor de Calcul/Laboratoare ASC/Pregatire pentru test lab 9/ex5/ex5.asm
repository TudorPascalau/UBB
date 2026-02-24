bits 32

global start        

extern exit, printf, scanf, fopen, fprintf, fclose   
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

; Se da in data segment un sir de exact 10 caractere
; Sa se citeasca un numar natural n reprezentat pe un octet (daca se introduce o valoare mai mare programul va afisa un mesaj coresp si se va opri din executie)
; Sa cere sa se creeze n fisiere, fiecare avand numele output-i.txt, unde i=0,n
; Sa se scrie in fiecare fisier primele (i+1) caractere din sirul dat (sau maxim 10)

segment data use32 class=data
    
    sir db "abcdefghij"
    output db "output"
    destinatie times 10 db 0
    
    mesaj db "n este mai mare decat un octet" , 0
    
    n dd 0
    format_citire db "%d", 0
    
    nume_fisier times 20 db 0
    mod_acces db "w", 0
    descriptor dd 0

segment code use32 class=code

    not_octet:
        push dword mesaj
        call [printf]
        add esp, 4
        jmp final

    start:
    
        push dword n ; citim n
        push dword format_citire
        call [scanf]
        add esp, 4*2
        
        cmp dword [n], 255 ; verificam daca n incape pe un octet
        ja not_octet
        
        cmp dword [n], 10 ; cate fisiere creez
        jb n_mic 
        jae n_mare
        
        n_mare:
        mov ecx, 10
        jmp fisiere
        
        n_mic: 
        mov ecx, [n]
        jmp fisiere

        fisiere:
        
        repeta_fisier:
            cld ; pregatim parcurgerea
            mov esi, output
            mov edi, nume_fisier
            
            mov ebx, ecx ; salvam ecx
            
            mov ecx, 6 ; lungimea cuvantului output
            repeta_output:
                movsb
                loop repeta_output ; nume_fisier = "output"
                
            mov al, '-'
            stosb
            
            mov eax, ebx
            dec eax 
            add eax, '0' ; formam cifra
            stosb ; nume_fisier = "output-i"
            
            mov al, '.'
            stosb
            mov al, 't'
            stosb
            mov al, 'x'
            stosb
            mov al, 't'
            stosb
            mov al, 0
            stosb ; nume_fisier = "output-i.txt" , 0
            
            push dword mod_acces ; deschidem fisierul
            push dword nume_fisier
            call [fopen]
            add esp, 4*2
            
            cmp eax, 0
            je skip_fisier
            mov [descriptor], eax ; salvam descriptorul
            
            cld
            mov esi, sir
            mov edi, destinatie
            
            mov ecx, ebx
            repeta_rezultat:
                movsb
                loop repeta_rezultat
                
            mov al, 0
            stosb
                
            push dword destinatie
            push dword [descriptor]
            call [fprintf]
            add esp, 4*2
            
            push dword [descriptor]
            call [fclose]
            add esp, 4
            
            skip_fisier:
            
            mov ecx, ebx
            dec ecx
            jnz repeta_fisier
            
        
        final:
        push    dword 0      
        call    [exit]       
