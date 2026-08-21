bits 32

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data

        a dw 1234h ; 4660
        b db 5bh ; 91
        c resd 1 ; FFFFB4B8 4,294,948,024
        
        ;Dublucuvantul c se formeaza astfel:
        ; - bitii 0-2 ai lui c au valoarea 0
        ; - bitii 3-5 ai lui c au valoarea 1
        ; - bitii 6-9 ai lui c coincid cu bitii 11-14 ai lui a
        ; - bitii 10-15 ai lui c coincid cu bitii 1-6 ai lui b
        ; - bitii 16-31 ai lui c au valoarea 1
        
        ; Sa se efectueze in interpretarea fara semn operatia ((a+c)/b+c)*2-a


segment code use32 class=code
    start:
    
        mov dword [c], 11111111111111110000000000111000b ; modificam bitii pentru a coincide cu enuntul
        
        mov ax, [a] ; modificam din a+4 in a pentru a muta valoarea lui a
        and ax, 0111100000000000b ; izolam bitii 11-14
        shr ax, 5 ; mutam la dreapta cu 5 pozitii
        or [c], ax ; renuntam la byte deoarace nu reprezinta dimensiunea corecta
        mov al, [b]
        mov ah, 0
        and ax, 07eh ; inlocuim feh cu 7eh pentru a avea masca 0000000001111110 si sa izolam bitii 1-6
        shl ax, 9 ; inlocuim al cu ax ; mutam la stanga cu 9 pozitii
        or [c], ax; inlocuim or cu xor pentru a pune in rezultat
        
        mov eax, 0 ; inlocuim cwde pentru a efectua operatii in interpretare fara semn
        mov ax,[a]
        add eax,[c] ; inlocuim ax cu eax pentru a avea dimensiunea corecta
        mov edx, 0
        movzx ebx, byte[b] ; inlocuim movsz cu movzx pentru a efectua operatii in interpretarea fara semn
        div ebx
        add eax, [c]
        mov ebx, 2
        mul ebx ; inlocuim imul cu mul pt interpretare fara semn
        xchg eax, ebx ; ebx = eax
        xchg ecx, edx ; ecx = edx
        movzx eax, word[a]
        mov edx, 0
        sub ebx,eax
        sbb ecx,edx ; interschimbam sub si sbb
        
        push    dword 0      
        call    [exit]       
