bits 32

;functii din C
extern _citireSirC
extern _str3

extern _printf

; asamblare globala
global _asmConcat   

; segment date public - date din afara
segment data public data use32
    lenRez dd 0
    adresaSirRezultat dd 0
    adresaSirParam dd 0
    adresaSirCitit dd 0 
    mesaj db "Sirul 2 citit din modul asm: ", 0

; segment public - codul poate fi partajat in afara
segment code public code use32

;int asmConcat(char[], char[])
_asmConcat:
    ;Codul de intrare
    push ebp
    mov ebp, esp
    sub esp, 4*3 ; Rezervam 4*3 octeti pentru sirul citit de la tastatura
    
    ;Cod apel
    mov eax, [ebp+8] ; eax = argument 2
    mov [adresaSirParam], eax
    
    mov eax, [ebp+12] ; eax = argument 1
    mov [adresaSirRezultat], eax
    
    mov [adresaSirCitit], ebp ; salvam adresa sirului care va fi citit
    sub dword [adresaSirCitit], 4*3 ; adresaSirCitit = ebp - 12
    
    ; apelam functia citireSirC din C pentru a citi sirul 2
    push dword mesaj
    call _printf
    add esp, 4*1 ; curatam stiva
    
    push dword [adresaSirCitit]
    call _citireSirC
    add esp, 4*1 ; curatam stiva
    
    ; concatenam sirurile
    
    ; copiem sirul 1 (transmis ca parametru) in sirul rezultat
    cld
    mov esi, [adresaSirParam]
    mov edi, [adresaSirRezultat]
    mov ecx, 10
    rep movsb
    add dword [lenRez], 10
    
    ; copiem sirul 2 citit folosind citireSirC in sirul rezultat
    
    mov esi, [adresaSirCitit]
    mov ecx, 10
    rep movsb
    add dword [lenRez], 10
    
    ; copiem sirul 3 variabila globala in sirul rezultat
    
    mov esi, _str3
    mov ecx, 10
    rep movsb
    add dword [lenRez], 10
    
    ;Codul de iesire
    
    add esp, 4*3 ; Eliberam spatiul alocat pe stiva
    mov esp, ebp ; Refacem cadrul de stiva
    pop ebp
    
    mov eax, [lenRez] ; ce returneaza functia
    
    ret