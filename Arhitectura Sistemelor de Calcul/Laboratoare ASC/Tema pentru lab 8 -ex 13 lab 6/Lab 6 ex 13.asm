bits 32

global start        

extern exit               
import exit msvcrt.dll    

;Se da un sir S de dublucuvinte.
;Sa se obtina sirul D format din octetii inferiori ai cuvintelor inferioare din elementele sirului de dublucuvinte, care sunt multiplii de 7.

segment data use32 class=data
    
    s dd 12345607h, 1a2b3c15h, 13a33312h
    len equ ($-s)/4
    
    d times len db 0
    
    sapte db 7

segment code use32 class=code
    start:
    
        mov ecx, len ; pregatim loop-ul
        jecxz final 

        mov esi, s ; pregatim instructiunile de operatii pe siruri
        mov edi, d
        cld
        
        repeta:
        
            lodsw ; in ax vom avea cuvantul inferior al dublucuvantului curent
            and ax, 00ffh ; pastram doar octetul inferior
            mov bl, al ; salvam octetul inferior
            
            div byte[sapte] ; in ah avem restul impartirii
            cmp ah, 0 ; verificam multiplu al lui 7
            jnz nonmultiplu
            
            mov al, bl ; punem la loc octetul inferior
            stosb
        
            nonmultiplu:
            lodsw ; incarcam octetul superior al dublucuvantului curent
            loop repeta
        
        final:
            push    dword 0      
            call    [exit]       
