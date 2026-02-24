bits 32

global _ELIMINARE
extern _printf

segment data public data use32

    format_string db "%s", 0

segment code public code use32
;void ELIMINARE (char s*, char s*)
_ELIMINARE:
        push ebp
        mov ebp, esp
        
        push esi
        push edi
        
        cld
        mov esi, [ebp+8]
        mov edi, [ebp+12]
        
        .parse:
        lodsb
        
        cmp al, 0
        je .done_parse
        
        cmp al, '!'
        je .parse
        cmp al, '#'
        je .parse
        cmp al, '@'
        je .parse
        cmp al, '%'
        je .parse
        cmp al, '&'
        je .parse
        cmp al, '-'
        je .parse
        cmp al, '+'
        je .parse
        cmp al, '*'
        je .parse
        cmp al, '('
        je .parse
        cmp al, ')'
        je .parse
        
        stosb
        jmp .parse
        
        .done_parse:
        mov al, 0
        stosb
        
        push dword [ebp+12]
        push format_string
        call _printf
        add esp, 4*2
        
        pop edi
        pop esi
        
        mov esp, ebp
        pop ebp
        
        ret