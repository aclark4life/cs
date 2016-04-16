; shield.asm

SHIELD_WIDTH 		  equ	5
INITIAL_SHIELD_1_LOCATION equ	1401H		; 20, 1

	public	shield_p1_left
	public	shield_p1_right
	public	shield_p1_hit

	include	screen.h

data			segment	public
p1_shield_location	dw	INITIAL_SHIELD_1_LOCATION
shield_string		db	SHIELD_WIDTH dup ('_')
blank_shield_string	db	SHIELD_WIDTH dup (' ')
data			ends


code	segment	public byte 'code'
	assume cs:code, ds:data

;
; purpose:  check if a rock hit a shield
; input:    dx = lower left corner of rock, cl = rock width
; output:   zr flag set if hit, clear otherwise.  
; destroys: nothing
;
shield_p1_hit	proc	near
	push	ax
	push	dx
	push	si

	...


hit:
	...

	test	al, 0				; hit!  set ZF = 1
	
no_hit:						; for jumps, ZF = 0 
	pop	si
	pop	dx
	pop	ax
	ret
shield_p1_hit	endp


;
; purpose:  move player one's shield to the left
; input:    nothing
; output:   nothing (player 1's shield location is updated and is screen) 
; destroys: nothing
;
shield_p1_left	proc	near
	push	dx
	push	si

	mov	dx, p1_shield_location
	cmp	dl, 0
	jle	cant_move_left

	lea	si, blank_shield_string
	call	draw_shield

	sub	dl, 1				; the actual move!
	mov	p1_shield_location, dx
	lea	si, shield_string
	call	draw_shield

cant_move_left:
	pop	si
	pop	dx
	ret
shield_p1_left	endp


;
; purpose:  move player one's shield to the right
; input:    nothing
; output:   nothing (player 1's shield location is updated and is screen) 
; destroys: nothing
;
shield_p1_right	proc	near
	push	dx
	push	si

	mov	dx, p1_shield_location
	cmp	dl, SCREEN_WIDTH-SHIELD_WIDTH-1
	jge	cant_move_right

	lea	si, blank_shield_string
	call	draw_shield

	inc	dl
	mov	p1_shield_location, dx

	lea	si, shield_string
	call	draw_shield

cant_move_right:
	pop	si
	pop	dx
	ret
shield_p1_right	endp


;
; purpose:  draw a shield :)
; input:    dx holds location, si points to the string to print
; output:   nothing (screen is updated)
; destroys: nothing
;
draw_shield	proc	near
	push	ax
	push	cx
	push	dx

	cld
	mov	cx, SHIELD_WIDTH
draw_loop:
	call	screen_locate
	lodsb
	call	screen_write_char
	inc	dl
	loop	draw_loop

	pop	dx
	pop	cx
	pop	ax
	ret
draw_shield	endp

code	ends
	end
