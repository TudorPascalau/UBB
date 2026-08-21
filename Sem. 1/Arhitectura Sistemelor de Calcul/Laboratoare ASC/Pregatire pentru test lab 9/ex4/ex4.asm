    bits 32

    global start        

    extern exit, fopen, fprintf, fclose, scanf, strlen  
    import exit msvcrt.dll
    import fopen msvcrt.dll
    import fprintf msvcrt.dll
    import fclose msvcrt.dll
    import scanf msvcrt.dll
    import strlen msvcrt.dll

    ; Se da un sir de caractere care contine mai multe cuvinte separate prin spatiu (inclusiv ultimul caracter din sir este spatiu)
    ; Programul va crea pentru fiecare cuvant din sir un nou fisier care va contine nimarul de caractere din cuvant si care va avea ca nume cuvantul respectiv.

    ; Varianta sir text citit de la tastatura

    segment data use32 class=data
        
        cuvant times 30 db 0
        format_citire db "%s", 0
        format_scriere db "%d", 0
        
        nume_fisier times 40 db 0
        mod_acces db "w", 0
        descriptor dd -1

    segment code use32 class=code
        start:
        
            citeste:
        
            push dword cuvant
            push dword format_citire
            call [scanf]
            add esp, 4*2
            
            cmp eax, 1 ; verificam daca a citit un cuvant
            jne gata_citire
            
            push dword cuvant
            call [strlen]
            add esp, 4
            
            mov ebx, eax ; salvam lungimea
            
            cld
            mov ecx, ebx ; ecx !=0
            mov esi, cuvant
            mov edi, nume_fisier
            
            repeta:
                movsb ; punem literele cuvantului in nume fisier
                loop repeta
                
            mov al, '.'
            stosb
            mov al, 't'
            stosb
            mov al, 'x'
            stosb
            mov al, 't'
            stosb
            mov al, 0
            stosb
            
            push dword mod_acces ; deschidem fisier
            push dword nume_fisier
            call [fopen]
            add esp, 4*2
            
            cmp eax, 0 ; verificam daca s-a deschis fisierul
            je skip_file
            
            mov [descriptor], eax ; salvam descriptor
            
            push ebx ; scriem in fisier lungimea cuvantului
            push dword format_scriere
            push dword [descriptor]
            call [fprintf]
            add esp, 4*3
            
            push dword [descriptor] ; inchidem fisierul
            call [fclose]
            add esp, 4
            
            skip_file:
            jmp citeste
            
            gata_citire:
            
            push    dword 0      
            call    [exit]       
