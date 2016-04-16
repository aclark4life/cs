From binkley Fri Dec  8 15:04:06 1995
Subject: scankb.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 15:04:02 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 1976      
Status: O

         .radix 16
code     segment public 'code'
         assume cs:code
; print out scan codes returned from keyboard
; First try just prefixing int, geting char
; Next try; prefix all in/out in int 09
         jmp   setin
newkb:
         push  ax
         in    al,60                   ; get char
         pushf                         ; far call old 09
         db    09a                     ; define a far call
off      dw    ?
segmnt   dw    ?

         call  print_hex
         pop   ax
         iret
; prints the word in ax as four hex digets
print_hex:
         push  dx
         push  bx
         mov   bx,ax                   ; save value
         mov   dl,bl                   ; hi nibble BL
         call  shift_prn
         mov   dl,bl                   ; low nibble BL
         call  prn
         mov   ax,0e20                 ; print blank
         int   10
         pop   bx
         pop   dx
         ret


shift_prn:                             ; niale in dl high entry
         shr   dl,1
         shr   dl,1
         shr   dl,1
         shr   dl,1
prn:                                   ; nibble in dl low entery
         and   dl,0f                   ; wanted nibble
         add   dl,30H                  ; up to diget level
         cmp   dl,3aH                  ; letter (a-f)
         jl    no
         add   dl,7                    ; adjust for letter
no:
;        mov   ah,02                   ; print char
;        int   21
         mov   ah,0e
         mov   al,dl                   ; tty write
         int   10

         ret



setin:
         push  cs
         pop   ds
         assume ds:code
         mov   ax,3509                 ; get int 09
         int   21

         mov   off,bx                  ; mov into jump
         mov   segmnt,es
         lea   dx,newkb                ; set int 09
         mov   ax,2509
         int   21

         lea   dx,setin+101              ; resident part
         int   27

code     ends
         end


