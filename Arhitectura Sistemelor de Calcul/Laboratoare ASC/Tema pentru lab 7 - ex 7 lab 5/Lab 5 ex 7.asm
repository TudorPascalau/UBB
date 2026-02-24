bits 32

global start        

extern exit               
import exit msvcrt.dll    

; Se dau doua siruri de octeti S1 si S2 de aceeasi lungime. 
; Sa se obtina sirul D prin intercalarea elementelor celor doua siruri

segment data use32 class=data

    s1 db 1,3,5,7
    len1 equ $-s1
    
    s2 db 2,4,6,8
    len2 equ $-s2
    
    d times len1+len2 db 0


segment code use32 class=code
    start:
        
        ; formam indicii pari ai sirului a sirului
        mov ecx, len1
        mov esi, 0
        mov edi, 0
        jecxz Sfarsit
        Repeta1:
        
            mov al, [s1+esi]
            mov [d+edi], al
            inc esi
            add edi, 2
            
        loop Repeta1
            
        ; formam indicii impari ai sirului
        mov ecx, len2
        mov esi, 0
        mov edi, 1
        jecxz Sfarsit
        Repeta2:
        
            mov al, [s2+esi]
            mov [d+edi], al
            inc esi
            add edi, 2
            
        loop Repeta2
            
        Sfarsit:
        
        push    dword 0      
        call    [exit]       
