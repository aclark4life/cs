From binkley Fri Dec  8 14:57:15 1995
Subject: dollar.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 14:57:11 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 1654      
Status: O

; dollar.asm
;
;
; David Binkley
; CS 366
; Assignment 6 (Part 2)
; 11/23/93
;
		include	macros.h
TIMER_INT	equ	1cH
TIMER_INT_LOC	equ	4*TIMER_INT
TAU		equ	36
TRUE		equ	 1
FALSE		equ	 0
TTY		equ	10H
TTY_WRITE	equ	0eH
DOS		equ	21H
READ_CHARACTER	equ	01H
TERMINATE	equ	4cH
QUIT		equ	'Q'


code	segment	public byte 'code'
	assume  cs:code
main	proc	near
	mov	ax,cs
	mov	ds,ax
	assume	ds:code

        xor     ax,ax
        mov     es,ax 				; seg of interrupt vector table

	mov     currently_active,TRUE		; disable new timer interrupt
        mov     di,TIMER_INT_LOC		; intercept timer interrupt
	mov	ax,cs
	lea	bx,new_interrupt_handler
	cli
	xchg    es:0[di],bx			; offset then segment
        xchg    es:2[di],ax
	sti
	mov     hold_timer_ip,bx
	mov     hold_timer_cs,ax

	mov     count,TAU
	mov     currently_active,FALSE
lp:						; read and echo until QUIT character
        mov     ah,READ_CHARACTER
	int	DOS
	cmp     al,QUIT
	jne	lp

 	mov	ax,hold_timer_cs		; restore timer interrupt
	mov	bx,hold_timer_ip
	cli						
	mov     es:0[di], bx
	mov     es:2[di], ax
	sti

	exit	0
main	endp


;
; data smack in the middle of the code segment
; (so it can be referred to as cs:currently_active, cs:..., etc).
;
currently_active	db	?
count			dw	?
hold_timer_ip		dw	?
hold_timer_cs		dw	?

new_interrupt_handler proc	near
	cmp	cs:currently_active,TRUE	; don't run two copies
        je	done				; as the "same" time
	dec	cs:count
	jnz	done

	mov     cs:currently_active,TRUE
	push    ax
	mov     ah,TTY_WRITE
	mov	al,'$'
	int     TTY
	mov     cs:count,TAU
	pop	ax
	mov     cs:currently_active,FALSE

done:
	iret
new_interrupt_handler endp


code	ends
	end main

