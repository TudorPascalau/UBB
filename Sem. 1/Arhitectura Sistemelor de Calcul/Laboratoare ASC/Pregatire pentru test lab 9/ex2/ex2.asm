bits 32

global start        

extern exit, fopen, fprintf, fclose, scanf
import exit msvcrt.dll    
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll

; Se citesc numere de la tastatura pana cand se introduce numarul 0
; Toate numerele care sunt palindrom vor fi scrise in fisierul palindrom.txt, separate prin spatiu, urmate de toate care nu sunt palindrom
; La tastatura se vor introduce cel mult 100 de numere

segment data use32 class=data
    
        d resd 100
        a dd -1
        format_citire db "%d", 0
        
        nume_fisier db "palindrom.txt", 0
        mod_acces db "w", 0
        descriptor dd -1
        
        format_numar db "%d", 0
        format_spatiu db "%c", 0
        s db " "

segment code use32 class=code
    start:
    
        cld
        mov edi, d ; in sirul d punem nepalindrom
        mov esi, 0 ; contor numere nepalindrom
    
        push dword mod_acces ; deschidem fisierul
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0 ; verificam deschiderea
        je final
        mov [descriptor], eax ; salvam descriptorul
        
    
        mov ecx, 100 ; pregatim citirea
        citeste:
            push ecx
            push dword a
            push dword format_citire
            call [scanf]
            pop ecx
            add esp, 4*2
            
            cmp dword [a], 0
            je termina_citire
            
            push ecx ; salvam contor bucla
            
            mov eax, [a]
            mov ebx, eax ; copie
            mov ebp, 0 ; creem oglinditul
            
            oglindit:
                cmp eax, 0
                je ogl_gata
                
                mov edx, 0 ; edx:eax = eax
                mov ecx, 10
                div ecx ; eax = eax/10 ; edx = edx%10
                
                push eax ; salvam eax
                push edx ; salvam restul
                
                mov eax, ebp ; eax = ecx
                mul ecx ; edx:eax = eax*10 = ecx*10
                mov ebp, eax ; ebp = oglindit = ecx*10
                
                pop edx ; reluam restul
                add ebp, edx ; ecx = ecx*10 + 5
                
                pop eax ; revenim la eax
                
                jmp oglindit
                
            ogl_gata:
            
            cmp ebx, ebp
            je palindrom
            jne not_palindrom
            
            palindrom:
                push ecx
                push dword [a]
                push dword format_numar
                push dword [descriptor]
                call [fprintf]
                add esp, 4*3
                
                push dword [s]
                push dword format_spatiu
                push dword [descriptor]
                call [fprintf]
                add esp, 4*3
                pop ecx
                
                jmp revenire
                
            not_palindrom:
                mov eax, [a]
                stosd
                inc esi
            
            revenire:
            pop ecx
            dec ecx
            jnz citeste
            
        termina_citire:
        
        mov ecx, esi ; lungimea sirului de nepalindrom
        mov esi, d
        jecxz inchide
        
        repeta_nonpal:
            lodsd ; EAX = dublucuvant din d
            
            push ecx
            
            push eax
            push dword format_numar
            push dword [descriptor]
            call [fprintf]
            add esp, 4*3
            
            push dword [s]
            push dword format_spatiu
            push dword [descriptor]
            call [fprintf]
            add esp, 4*3
            
            pop ecx
            
            loop repeta_nonpal
        
        inchide:
        
        push dword [descriptor]
        call [fclose]
        add esp, 4
        
        final:
        
        push    dword 0      
        call    [exit]       
