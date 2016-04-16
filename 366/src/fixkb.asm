From binkley Fri Dec  8 15:03:57 1995
Subject: fixkb.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 15:03:50 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 1116      
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
	 cmp   al,0FAH		       ; check caps lock down
	 je    ignore

	 cmp   al,03AH		       ; check caps lock down
	 je    ignore

         pushf                         ; far call old 09
         db    09a                     ; define a far call
off      dw    ?
segmnt   dw    ?
	 jmp   done

ignore:
;jmp done
	 mov	al,20H
	 out	20H,al			; issue the EOI command

done:
         pop   ax
         iret

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


