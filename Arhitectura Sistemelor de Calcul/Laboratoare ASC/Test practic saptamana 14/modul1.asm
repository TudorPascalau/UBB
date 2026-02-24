bits 32

global _VERIFICARE
extern _printf

segment data public data use32

    string_speciale db "!#@%&-+*)(", 0
    mesaj_nu db "NU ", 0
    mesaj_da db "DA ", 0
    format db "%d", 0

segment code public code use32
;void VERFICARE(char *, int)

_VERIFICARE:
        push ebp
        mov ebp, esp
        
        push esi
        push edx
        push ebx
        push ecx
        
        cld
        mov edx, 0 ; numaram numarul de caractere
        mov esi, [ebp+8]
        mov ebx, [ebp+12] ; numarul L
        mov ecx, 0 ; setam pe 1 daca numarul contine caracterele speciale (presupunem ca nu contine)
        
        .parse:
        lodsb
        
        cmp al, 0
        je .done_parse
        
        cmp al, '!'
        je .contine
        cmp al, '#'
        je .contine
        cmp al, '@'
        je .contine
        cmp al, '%'
        je .contine
        cmp al, '&'
        je .contine
        cmp al, '-'
        je .contine
        cmp al, '+'
        je .contine
        cmp al, '*'
        je .contine
        cmp al, '('
        je .contine
        cmp al, ')'
        je .contine
        
        jmp .continue_parse
        
        .contine:
        mov ecx, 1
        
        .continue_parse:
        
        inc edx
        jmp .parse
        
        .done_parse:
        
        cmp edx, ebx
        jne .NU
        cmp ecx, 1
        jne .NU
        
        
        .DA:
        push dword mesaj_da
        call _printf
        add esp, 4
        jmp .done
        
        .NU:
        push dword mesaj_nu
        call _printf
        add esp, 4
        
        .done:
        
        pop ecx
        pop ebx
        pop edx
        pop esi
        
        mov esp, ebp
        pop ebp
        
        ret