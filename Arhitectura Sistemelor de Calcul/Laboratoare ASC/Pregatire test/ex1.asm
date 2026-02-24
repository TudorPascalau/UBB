bits 32

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    
    a dw 5
    b dw 10
    c dd 15
    
    

segment code use32 class=code
    start:
        
        ;calculam [(a*b+5)/10]*c = 75
        
        ;program corect calcul cu semn
        mov ax,[a]
        mov bx,[b]
        imul bx ; modificam ebx in bx, pentru a inmulti corect word cu word -> dx:ax = a*b
        mov bx, 5
        add ax, bx
        ; renuntam la stc, deoarece nu mereu se seteaza CF la adunarea ax, bx
        adc dx, 0 ; inlocuim 1 cu 0, pentru a aduna corect -> dx:ax = a*b+5
        mov bx, 10 ; inlocuim 0x10 cu 10, altfel am muta in bx valoarea 16
        idiv bx ; -> ax = (a*b+5)/10
        cwde ; renuntam la 1, pentru a nu avea eroare de asamblare
        mov ebx, [c]
        imul ebx; inlocuim ecx cu ebx pentru a inmulti corect -> edx:eax = (a*b+5)/10*c
        push edx ; inlocuim pop cu push pentru a pune pe stiva rezultatul
        push eax
        
        ;program corect fara semn
        mov eax, 0
        mov ebx, 0 ; resetam valorile pentru a efectua calcule noi
        mov ax, [a]
        mov bx, [b] ; inlocuim ebx cu bx si b+2 cu b, pentru a pune in bx valoarea din memorie a lui b
        mul bx ; inlocuim imul cu mul, deoarece facem inmultire fara semn
        mov bx, 5
        add ax, bx ; inlocuim cx cu bx pentru a aduna corect
        ; renuntam la stc, deoarece nu mereu se seteaza CF la adunarea ax, bx
        adc dx, 0 ; -> dx:ax = a*b+5
        mov bx, 10
        div bx ; -> ax =(a*b+5)/10 
        push word 0
        push ax
        pop eax; eax = (a*b+5)/10 
        mov ebx, [c]
        mul ebx ; edx:eax = (a*b+5)/10 
        pop ebx 
        pop ecx ; -> ecx:ebx =  (a*b+5)/10*c fara semn
        clc
        add eax, ebx
        adc edx, ecx ; inlocuim add cu adc pentru a face adunarea intre qworduri corect
        
        push    dword 0      
        call    [exit]       
