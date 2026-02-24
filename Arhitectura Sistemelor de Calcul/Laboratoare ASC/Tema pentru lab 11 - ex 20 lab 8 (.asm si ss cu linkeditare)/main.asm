bits 32

global start        

extern exit, fopen, fclose, fscanf, printf 
import exit msvcrt.dll  
import fopen msvcrt.dll
import fclose msvcrt.dll
import fscanf msvcrt.dll
import printf msvcrt.dll

global descriptor, format_citire, numar

extern citeste

;Se citeste din fisierul numere.txt un sir de numere. 
;Sa se determine sirul destinatie D care contine numerele din sirul initial cu valorile dublate dar in ordine inversa din sirul initial. 
;Sa se afiseze sirul obtinut pe ecran.
;Ex: s: 12, 2, 4, 5, 0, 7 => 14, 0, 10, 8, 4, 24

segment data use32 class=data
    
    nume_fisier db "numere.txt", 0
    mod_acces db "r", 0
    
    descriptor dd -1
    format_citire db "%d", 0
    
    numar dd 0
    
    format_afisare db "%d ", 0

segment code use32 class=code
    start:
    
        ; deschidem fisierul
        
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0 ; verificam deschiderea corecta
        je done
        
        mov [descriptor], eax ; salvam descriptorul
        
        mov ebx, 0 ; in ebx contorizam cate numere citim
        
        ; incepem citirea
        repeta_citire:
            call citeste
            
            cmp eax, 1
            jne gata_citire ; daca eax != 1 -> eroare la citire (sau am terminat)
            
            mov eax, [numar]
            mov ecx, 2
            mul ecx ; edx:eax = numar*2 (presupunem ca lucram cu numere care incap pe dw) -> avem rezultat in eax
            
            push eax ; salvam pe stiva numerele ca sa le afisam in ordine inversa
            inc ebx
            
            jmp repeta_citire; reluam citirea pana iesim
        
        gata_citire:
        
        ; afisam numerele
        
        repeta_afisare:
            
            cmp ebx, 0
            je gata_afisare
            
            ; numarul urmator de afisat este implicit pe stiva 
            push format_afisare
            call [printf]
            add esp, 4*2 ; golim 2 dword de pe stiva
        
        
            dec ebx
            jmp repeta_afisare
        
        gata_afisare:
        
        
        ; inchidem fisierul
        push dword [descriptor]
        call [fclose]
        add esp, 4
        
        done:
        
        push    dword 0      
        call    [exit]       
