From binkley Fri Dec  8 14:57:11 1995
Subject: div.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 14:57:07 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 1876      
Status: O

; div.asm
;
; David Binkley
; CS 366
; Assignment 6 (Part 1)
; 11/23/93
;
		include	macros.h

DIV_BY_ZERO_INT	equ	0
DIV_BY_ZERO_LOC	equ	4*DIV_BY_ZERO_INT
CR		equ	13
LF		equ	10
TTY		equ	10H
TTY_WRITE	equ	0eH
DOS		equ	21H
READ_CHARACTER	equ	01H
TERMINATE	equ	4cH
QUIT		equ	'Q'
N		equ	0ABCH
MAXINT		equ	7FFFH


code	segment	public byte 'code'
	extrn	printAXhex:near
	extrn	print_blank:near, crlf:near
	extrn	get_number:near
	assume  cs:code

main	proc	near
	assume	ds:data
        xor     ax,ax
        mov     es,ax 				; seg of interrupt vector table

	mov	ax,seg data
	mov 	ds,ax

        mov     di,DIV_BY_ZERO_LOC		; intercept /0 interrupt
	mov	ax,cs
	lea	bx,new_interrupt_handler
	cli
	xchg    es:0[di],bx			; offset then segment
        xchg    es:2[di],ax
	sti
	mov     hold_div_by_0_ip,bx
	mov     hold_div_by_0_cs,ax


lp:						; loop until QUIT character
        mov     ah,READ_CHARACTER
	int	DOS
	cmp     al,QUIT
	je	exit_program

	call	get_number			; get and echo N
	call	print_blank

	xor	dx,dx				; divide 0:N by bx
	mov	bx,ax				
	mov	ax,N
	idiv	bx
	call	printAXhex
	call	crlf
	jmp	lp

exit_program:
 	mov	ax,hold_div_by_0_cs		; restore timer interrupt
	mov	bx,hold_div_by_0_ip
	cli						
	mov     es:0[di], bx
	mov     es:2[di], ax
	sti

	exit	0
main	endp



;
; new_interrupt_handler is invoked whenever there is a divide by zero
; input: nothing
; output: ax, and dx hold MAXINT
; destroys: nothing (including flags)
;

new_interrupt_handler proc	near
	push	si
	push	es
	mov	ax,seg data
	mov	es,ax
	lea	si,message

next_char:			; can't use print macro here! Why?
	lodsb
	cmp	al,'$'
	je 	done
	mov     ah,TTY_WRITE
	int     TTY
	jmp	next_char

done:
	mov	ax,MAXINT
	mov	dx,MAXINT
	pop	es
	pop	si
	iret
new_interrupt_handler endp

code	ends


data	segment
message			db	'divide by zero',CR,LF,'$'
hold_div_by_0_ip	dw	?
hold_div_by_0_cs	dw	?
data	ends
	end	main

