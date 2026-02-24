bits 32
global start        
extern exit
import exit msvcrt.dll

; Sa se determine si sa se salveze in memorie ultimii 3 biti ai rezultatului urmatoarei operatii, in interpretarea CU SEMN:
; d*d*d-(17+x)/(a*a*c-b/c+2)   ; a,b,c-byte; d-word; x-qword
segment data use32 class=data
    rezultat resb 1
    a db 2
    b db -15
    c db -3
    d dw 3
    x dq 13 ; G schimbam dw in dq pentru a defini corect qword
segment code use32 class=code
    start:
    
        mov AL, [a] ; al=a
        imul AL ; ax=a*a
        mov BX, AX ; bx = a*a
        mov AL, [c]
        cbw ; ax=c
        imul bx ; dx:ax=a*a*c
        mov BX, AX
        mov CX, DX
        mov AL, [b] ; al=b
        cbw ; G crestem dimensiunea pentru a putea imparti
        idiv byte [c] ; al = b/c
        cbw ; G inlocuim cwd cu cbw pentru a avea dimensiunile corecte ; ax=b/c
        sub BX, AX
        sbb CX, DX ; G inlocuim sub cu sbb pentru a scadea corect
        add BX, 2
        adc CX, 0 ; G adaugam adc in caz ca adunarea bx+2 produce transport
        ; cx:bx = (a*a*c-b/c+2)
        push CX ; G schimbam ordinea operatiilor de push
        push BX
        pop EBX ; ebx = (a*a*c-b/c+2)
        mov EAX, [x]
        mov EDX, [x+4] ; G schimbam x in x+4, pentru a retine corect val lui x in qword edx:eax 
        add EAX, 17 
        adc EDX, 0 ; edx:eax = (17+x) 
        idiv EBX ; G inlocuim div cu idiv pt a inmulti cu semn; eax = (17+x)/(a*a*c-b/c+2)
        mov EBX, EAX ; ebx = (17+x)/(a*a*c-b/c+2)
        mov AX, [d] ; G inlocuim EAX cu AX pentru a corespunde dimensiunilor
        imul word [d]; G modificam mul [d] in imul word [d], pt a specifica dim operatiei si a inmulti in interpret cu semn ; dx:ax = d*d
        push DX
        push AX
        pop ECX ; ecx=d*d
        mov AX, [d]
        cwde ;eax=d
        imul ECX ; G schimbam eax in ecx pentru a inmulti corect ; edx:eax = d*d*d
        push EBX ; punem pe stiva (17+x)/(a*a*c-b/c+2)
        mov EBX, EAX
        mov ECX, EDX ; dword ecx:ebx = d*d*d
        pop EAX ; eax = (17+x)/(a*a*c-b/c+2)
        cdq ; edx:eax = (17+x)/(a*a*c-b/c+2)
        sub EBX, EAX
        sbb ECX, EDX
        and EBX, 7 ; 7 = 00...00111b 
        mov byte [rezultat], BL ; G modificam rezultat in byte [rezultat] pentru a nu avea eroare de asamblare
        push dword 0
        call [exit]
