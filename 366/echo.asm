From binkley Fri Dec  8 14:57:26 1995
Subject: echo.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 14:57:21 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 1082      
Status: O

; echo.asn

CR 	EQU	0dH
LF	EQU	0aH


data segment
buffer	db	80,?,80 dup('#')
	db	'$'
byebye	db	'bye now!$'
crlf_msg	db	CR, LF, '$'
data ends

code segment byte public 'code'
	assume cs:code
main	proc	near
	mov	ax, seg data
	mov	ds,ax
	assume	ds:data

	mov	ah,0aH
	lea	dx, buffer    		; ds:dx points to buffer
	int	21H

	mov 	bl,buffer+1
	xor	bh,bh			; i.e.   mov bh, 0  FAST
	mov	buffer+2[bx], '$'    
   
        ; add a '$'
	
	call	crlf

        ;mov	ah, 09H
	lea	dx, buffer+2
	call	binkleys_dos_print
	;int	21H

	mov 	ah, 09H
	lea	dx, byebye
	int	21H

	mov	ah,4cH
	int	21H


	
main	endp

; input: ds:dx points to a string to print
; output: nothing (prints to the screen)

binkleys_dos_print	proc near
	push	ax
	push	dx
	push	si

	mov	si,dx
; loop through the string printing each character until a '$' is reached
loop:
	mov	al,[si]
	inc	si
	cmp	al,'$'
	je	done
	mov	ah, 0EH
	int	10H
	jmp 	loop

done:
	pop	si
	pop	dx
	pop	ax
	ret
binkleys_dos_print	endp


crlf	proc	near
	push	ax
	push	dx

	lea	dx, crlf_msg
	mov	ah, 09H
	int	21H

	pop	dx
	pop	ax
	ret
crlf	endp

code	ends
	end

