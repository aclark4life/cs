From binkley Fri Dec  8 14:57:31 1995
Subject: timebomb.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 14:57:26 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 1948      
Status: O

; Time Bomb
; a TSR!  (be nice)

	include dos.h
	include macros.h
	include screen.h

TIMER_INT       equ     1cH
TIMER_INT_LOC   equ     4*TIMER_INT
TAU             equ     16*60

	extrn print_string:near
	extrn locate:near

code	segment	public byte 'code'
	assume cs:code, ds:nothing
;
; data smack in the of the code segment
; (so it can be referred to as cs:currently_active, cs:..., etc).
;
currently_active	db	?
count			dw	?
message			db	'  BOOM!  ', 0
m2	db 'm2!', 0


main	proc	near
	
        xor     ax,ax
        mov     es,ax 				; seg of interrupt vector table

	mov     currently_active,TRUE		; disable new timer interrupt
        mov     di,TIMER_INT_LOC		; intercept timer interrupt
	mov	ax,cs
	lea	bx,new_interrupt_handler
	cli
	mov     es:0[di],bx			; offset then segment
        mov     es:2[di],ax
	sti

	mov     count,TAU
	mov     currently_active,FALSE

        mov     ah, 31H
	mov     al, STATUS_OK
	mov     dx, 264H   ; 64 paragraphs = 1K   
	int	DOS_SERVICE

	exit 	STATUS_OK
main	endp


;purpose:  replacement interrupt handler
;input:    active flag and count in CODE segment 
;output:   nothing (calls update_vogons every TAU interrupts)
;destroys: nothing [[ interrupt handlers cannot destroy anything!]]
new_interrupt_handler proc	near
	assume	ds:nothing

	cmp	cs:currently_active,TRUE	; don't run two copies
        je	done				; at the "same" time
	dec	cs:count
	jnz	done

	mov     cs:currently_active,TRUE
	call	print_message
	mov     cs:count,TAU
	mov     cs:currently_active,FALSE

done:
	iret
new_interrupt_handler endp


;purpose: update the vogons
;input:     vogon array in segment 'data'
;output:    nothing (vogons are updated across screen)
;destroys:  nothing
print_message	proc	near
	push	si
	push	ds

	push	cs			; move cs to ds using the stack
	pop	ds
 
	push	dx
        mov	dx,0b22H
	call	locate
	pop	dx

	lea	si, message
	call	print_string

	pop	ds
	pop	si
	ret
print_message	endp

code	ends
	end main

