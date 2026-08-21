bits 32

global _parse_intsAsm

segment data public data use32

segment code public code use32
;int parse_intsAsm(char* , int* )
_parse_intsAsm:
        ;Codul de intrare
        push ebp
        mov ebp, esp
        sub esp, 4*2 ; alocam spatiu pentru doua variabile locale
        
        ;salvam registri volatili cu care lucram
        push ebx
        push esi
        push edi
        
        ;Codul de apel
        
        ; Pregatim parcurgerea sirului de caractere
        mov esi, [ebp+8]
        mov edi, [ebp+12]
        mov dword [ebp-8], 0 ; in ebp-8 vom contoriza numarul de intregi
        mov dword [ebp-4], 1 ; presupunem numar pozitiv
        mov ebx, 0 ; in ebx vom transforma intregul din caractere
        cld
        
        .parcurgere:
        ; in eax gasim caracterul
        xor eax, eax
        lodsb ; eax = al = caracter curent
        
        cmp al, 0 ;verificam sfarsitul sirului
        je .done
        
        cmp al, 10 ; verificam endline
        je .done
        
        cmp al, '-' 
        jne .pozitiv
        mov dword [ebp-4], -1 ; schimbam semnul daca e negativ
        jmp .parcurgere ; trecem la urmatorul
        
        .pozitiv: ; sarim peste schimbare daca e pozitiv / ramane 1
        
        cmp al, ' ' ; daca am dat de un nou spatiu, depozitam noul int
        je .load_int
        
        ;daca nu se realizeaza unul dintre salturile anterioare => avem numar
        ;construim numarul
        
        ; c = eax - '0'
        sub eax, '0'
        
        ; ebx = ebx*10+c
        imul ebx, ebx, 10
        add ebx, eax
        
        jmp .parcurgere ; reluam parcurgerea
        
        
        .load_int:
        ;inmultim cu semnul
        imul ebx, [ebp-4]
        
        ; incarcam intregul
        mov eax, ebx
        stosd
        inc dword [ebp-8]
        
        xor ebx, ebx ; resetam numarul
        mov dword [ebp-4], 1 ; presupunem numar pozitiv
        
        jmp .parcurgere ; reluam parcurgerea
        
        .done:
        ; incarcam ultimul intreg
        ;inmultim cu semnul
        imul ebx, [ebp-4]
        
        ; incarcam intregul
        mov eax, ebx
        stosd
        inc dword [ebp-8]
        
        ; nu mai reluam parcurgerea
        
        ;salvam rezultatul in eax
        mov eax, [ebp-8]
        
        ;Restauram registrii
        pop edi
        pop esi
        pop ebx
        
        ;Codul de iesire        
        add esp, 4*2
        mov esp, ebp
        pop ebp
        
        ret