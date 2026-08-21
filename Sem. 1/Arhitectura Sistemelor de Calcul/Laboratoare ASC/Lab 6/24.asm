bits 32

global start        

extern exit               
import exit msvcrt.dll    

;Dandu-se un sir de dublucuvinte, sa se obtina un alt sir de dublucuvinte in care se vor pastra doar dublucuvintele din primul sir care au un numar par de biti cu valoare 1.

segment data use32 class=data
    
    sir dd 123,456,789,258
    len equ ($-sir)/4
    
    dest resd len

segment code use32 class=code
    start:
        
        ; pregatim loop
        mov ecx, len
        mov esi, sir
        mov edi, dest
        
        cld ; DF = 0, stanga la dreapta
        jecxz final
        repeta:
        
            lodsd ; EAX <- [sir + pozitie_curenta]
            
            push ecx
            
            ;bucla care numara nr de biti de 1 din dublucuvantul actual
            mov edx, eax ; nu stricam eax
            mov ecx, 32 ; 32 de rotiri
            mov bl, 0
            numarare_biti:
                shr edx, 1 ; bitul iesit in dreapta se pastreaza in CF
                adc bl, 0
            loop numarare_biti
        
            pop ecx
            
            test bl, 1
            jnz skip 
            ; are numar par de biti 1
            stosd
            
            skip:
        
        loop repeta
        
        
        final:
        push    dword 0      
        call    [exit]       
