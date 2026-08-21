bits 32

global start        

extern exit, printf, scanf

import exit msvcrt.dll
import printf msvcrt.dll  
import scanf msvcrt.dll

; Sa se citeasca de la tastatura doua numere a si b (in baza 10) si sa se calculeze a+b. 
; Sa se afiseze rezultatul adunarii in baza 16.

segment data use32 class=data
    
        a dd 0
        b dd 0
        
        citire_a db "a=", 0 ; CR LF
        citire_b db "b=", 0
        
        formatinput db "%d", 0 ; numar decimal
        formatoutput db "a+b in baza 16 este %x", 0 ; rezultat in hexa

segment code use32 class=code
    start:
    
        push dword citire_a ; mesaj de citire
        call [printf]
        add esp, 4*1
        
        push dword a ; citirea lui a
        push dword formatinput
        call [scanf]
        add esp, 4*2
        
        push dword citire_b ; mesaj de citire
        call [printf]
        add esp, 4*1
        
        push dword b ; citirea lui b
        push dword formatinput
        call [scanf]
        add esp, 4*2
        
        mov eax, [a]
        add eax, [b] ; eax = a+b
        
        push eax
        push formatoutput
        call [printf]
        add esp, 4*2
        
        push    dword 0      
        call    [exit]       
