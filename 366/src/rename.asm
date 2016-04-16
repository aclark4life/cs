From binkley Fri Dec  8 14:57:34 1995
Subject: rename.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 14:57:31 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 999       
Status: O

        .radix 16

COMMAND_LINE_PARAMETERS_START  equ 82H

data	segment
errm    db    'Error$'
data	ends

code    segment
        assume	es:code,cs:code
        mov  	ax,ds
        mov  	es,ax

        mov  	cl,ds:[80]              ; calc len
        xor  	ch,ch
        dec  	cx                      ; ignore return
        jle  	error

        mov 	di,COMMAND_LINE_PARAMETERS_START
	mov	al, ' '
	repz	scasb			; skip initial blanks
	lea	dx, -1[di]		; start of first argument

	repnz	scasb			; skip over argument string
	mov	byte ptr -1[di], 0	; terminate with '\0'

	repz	scasb			; skip blanks

 	mov	bx,di
	add	bx,cx	
	mov	byte ptr [bx], 0	; terminate s2 with '\0'
	dec	di			; point to start of second string

        mov  	ah,56                   ; rename   ds:dx to es:di
        int  	21
        jc   	error
exit:
        mov  	ah,4c
        int  	21

error:
	mov	ax, seg data
	mov	ds, ax
        lea  	dx,errm
        mov  	ah,09
        int  	21
        jmp  	exit


code    ends
        end

