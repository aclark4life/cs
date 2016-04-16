; rocks.asm
;
; purpose: play the rocks "game"
; input:   nothing
; output:  nothing (screen is updated)
;
; 
;  A rock looks like this
;
;     ##
;    ####
;     ##
;
	include dos.h
	include	macros.h
	include screen.h
	include	random.h
	include	shield.h
	include	cities.h
	include image.h


MAX_ROCKS		equ	 5		; on screen at a time
NEW_ROCK_CHANCE 	equ	10
TAU			equ	 8 		; fast = 4;  slow = 12
ROCK_MAX_Y		equ	20		; how far down can a rock fall
ROCK_MAX_X		equ	SCREEN_WIDTH-5	; how far over can a rock "fall"

PLAYER_1_LEFT	equ	'4'
PLAYER_1_RIGHT	equ	'6'
QUIT		equ	'q'

TIMER_INT	equ	1cH
TIMER_INT_LOCATION equ	4*TIMER_INT
SEGMENT_PART	equ	2
OFFSET_PART	equ	0

; A rock record (struct) has 4 fields
upper_left_corner equ	0		; corner location as a word
upper_left_x	equ	0		; a byte
upper_left_y	equ	1		; a byte
active		equ	2		; a byte
momentum	equ	3		; a byte
ROCK_SIZE	equ	4		; number of bytes in a rock struct

ROCK_HEIGHT	equ	3
ROCK_WIDTH 	equ	4


data	segment	public
rocks		db MAX_ROCKS dup (ROCK_SIZE dup (?))
rock_image	db 0,0,' ',  1,0,'#',  2,0,'#',  3,0,' '
       		db 0,1,'#',  1,1,'#',  2,1,'#',  3,1,'#'
       		db 0,2,' ',  1,2,'#',  2,2,'#',  3,2,' '
ROCK_IMAGE_LENGTH equ  ($ - rock_image)/3
blank_rock	db 0,0,' ',  1,0,' ',  2,0,' ',  3,0,' '
		db 0,1,' ',  1,1,' ',  2,1,' ',  3,1,' '
       		db 0,2,' ',  1,2,' ',  2,2,' ',  3,2,' '
hold_timer_ip	dw ?
hold_timer_cs	dw ?
data	ends


stack	segment stack
	db	256 dup	(?)
stack	ends


code	segment	public byte 'code'
	assume  cs:code, ss:stack

; data in the code segment so it can be referenced as 
; cs:currently_active and cs:count

currently_active	db	?
count			dw	?

main	proc	near 
	mov	ax, seg data
	mov	ds, ax
	assume	ds:data

	call	cities_initialize
	call	cities_draw


	mov	cx, MAX_ROCKS		; initialize rocks
	lea	di, rocks

init_loop:
	mov	byte ptr ACTIVE[di], FALSE
	add	di, ROCK_SIZE
	loop	init_loop


	xor	ax, ax			; hook into timer interrupt
	mov	es, ax			; segment of interrupt vector table

	mov	currently_active, TRUE
	mov	ax, cs			; segment of new interrupt handler
	mov	bx, offset new_interrupt_handler

	cli				; interrupts off
	xchg	es:[TIMER_INT_LOCATION+SEGMENT_PART], ax
	xchg	es:[TIMER_INT_LOCATION+OFFSET_PART], bx
	sti				; interrupts back on
	
	mov	hold_timer_ip, bx
	mov	hold_timer_cs, ax


	mov	count, TAU		; set up count down timer
	mov	currently_active, FALSE


main_loop:
	mov	ah, DOS_READ_CHARACTER
	int	DOS_SERVICE

	cmp	al, QUIT
	je	finish

	cmp	al, PLAYER_1_LEFT
	jne	else2
	call	shield_p1_left
	jmp	main_loop

else2:
	cmp	al, PLAYER_1_RIGHT
	jne	main_loop

	call	shield_p1_right
	jmp	main_loop

finish:
	mov	ax, hold_timer_cs
	mov	bx, hold_timer_ip

	cli	
	mov	es:[TIMER_INT_LOCATION+SEGMENT_PART], ax
	mov	es:[TIMER_INT_LOCATION+OFFSET_PART], bx
	sti

	exit	STATUS_OK
main	endp


;
; purpose:  handle timer interrupts
; input:    nothing
; output:   nothing (rocks and cities are updated)
; destroys: nothing (hardware interrupt handlers can NOT destroy anything!)
;
new_interrupt_handler	proc	near
	assume	ds:nothing
	cmp	cs:currently_active, TRUE
	je	done
	dec	cs:count
	jnz	done

	mov	cs:currently_active, TRUE
	call	update_rocks
	mov	cs:count, TAU
	mov	cs:currently_active, FALSE

done:
	iret
new_interrupt_handler	endp	


;
; purpose:  update all active rocks
; input:    nothing
; output:   nothing (rocks and screen are updated)
; destroys: nothing
;
update_rocks	proc	near
	push	ax
	push	ds			; save DOS' data segment

	mov	ax, seg data
	mov	ds, ax			; move to our data segment
	assume	ds:data

	call	move_rocks
	call	new_rock_check

	pop	ds
	pop	ax
	ret
update_rocks	endp


;
; purpose:  check to see if a new rock should be created
; input:    nothing
; output:   nothing (rocks array is updated)
; destroys: nothing
;
new_rock_check	proc	near
	push	ax
	push	cx
	push	di

	mov	ax, NEW_ROCK_CHANCE
	call	random
	cmp	ax, NEW_ROCK_CHANCE
	jne	no_new_rock

	mov	cx, MAX_ROCKS		; for cx = MAX_ROCKS to 1
	lea	di, rocks

	...
	; find a non-active rock then set it to active with
	; a random x location on the top of the screen 
	
no_new_rock:
	pop	di
	pop	cx
	pop	ax
	ret
new_rock_check	endp


;
; purpose:  move the rocks 
; input:    nothing
; output:   nothing (rocks array and screen are updated)
; destroys: nothing
;
move_rocks	proc	near
	push	ax
	push	cx
	push	dx
	push	si
	push	di

	mov	cx, MAX_ROCKS		; for cx = MAX_ROCKS to 1
	lea	di, rocks

move_rock_loop:
	cmp	byte ptr active[di], TRUE
	jne	next

	push	cx
	lea	si, blank_rock
	mov	dx, upper_left_corner[di]
	mov	cx, ROCK_IMAGE_LENGTH
	call	image_draw
	pop	cx

	call 	move_a_rock
	cmp	byte ptr upper_left_x[di], ROCK_MAX_X
	jge	remove_rock

	cmp	byte ptr upper_left_y[di], ROCK_MAX_Y
	jl	keep_rock

	mov	dx, upper_left_corner[di]
	push	cx			; save around call
	mov	cl, ROCK_WIDTH
	call	cities_hit_check
	pop	cx
	jmp	remove_rock

keep_rock:
	push	cx
	lea	si, rock_image		; else draw the rock
	mov	dx, upper_left_corner[di]
	mov	cx, ROCK_IMAGE_LENGTH
	call	image_draw
	pop	cx
	jmp	next

remove_rock:
	mov	byte ptr active[di], FALSE

next:
	add	di, ROCK_SIZE
	loop	move_rock_loop

	pop	di
	pop	si
	pop	dx
	pop	cx
	pop	ax
	ret
move_rocks	endp

;
; purpose:  move a rock!
; input:    di points to the rock
; output:   nothing (rock and screen are updated)
; destroys: nothing
;
move_a_rock	proc	near
	push	cx
	push	dx

	mov 	dx, upper_left_corner[di]
	add	dh, ROCK_HEIGHT-1		; dx = lower left corner
	mov	cl, ROCK_WIDTH
	call	shield_p1_hit
	mov	dh, upper_left_y[di]		; dx = upper left corner
	jne	keep_going

	mov	byte ptr momentum[di], -3	; else bounce

keep_going:
	cmp	byte ptr momentum[di], 0
	jg	going_down

	dec	dh				; move up
	inc	byte ptr momentum[di]
	jnz	store
	mov	byte ptr momentum[di], 1
	jmp	store

going_down:
	inc	dh

store:
	inc	dl
	mov	upper_left_corner[di], dx
	
	pop	dx
	pop	cx
	ret
move_a_rock	endp
code	ends
	end	main
