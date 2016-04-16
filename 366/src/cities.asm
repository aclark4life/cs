; city.asm
; cities look like this ('.' is a blank)
;
; ....+ 
; ..*.* 
; *****
;
; dead cities look like this
; 
; .....      
; .....    
; (:-:)

MAX_CITIES		equ 	 5
CITY_SPACING		equ	15		; used 12 with 6 cities
FIRST_CITY_LOCATION	equ   1503H		; 24, 3
MAX_HITS		equ	 3
CITY_WIDTH		equ	 5
SCORE_DRAW_OFFSET	equ   0301H		; below city

	extrn	printAXhex:near
	include	dos.h
	include	screen.h
	include image.h

	public	cities_draw
	public	cities_hit_check
	public	cities_initialize


; city "struct"
HIT_COUNT	equ	0		; a word
LOCATION	equ	2		; a word
CITY_SIZE	equ	4

data	segment public
cities	db	MAX_CITIES dup( CITY_SIZE  dup(?))
city_image	db	0,0,' ',  1,0,' ',  2,0,' ',  3,0,'+', 4,0,' '
		db	0,1,' ',  1,1,'*',  2,1,' ',  3,1,'*', 4,1,' '
		db	0,2,'*',  1,2,'*',  2,2,'*',  3,2,'*', 4,2,'*'
CITY_IMAGE_LENGTH	equ	($ - city_image)/3
dead_city_image	db	0,0,' ',  1,0,' ',  2,0,' ',  3,0,' ', 4,0,' '
		db	0,1,' ',  1,1,' ',  2,1,' ',  3,1,' ', 4,1,' '
		db	0,2,'(',  1,2,':',  2,2,'-',  3,2,':', 4,2,')'
data	ends


code	segment public byte 'code'
	assume	cs:code, ds:data
;
; purpose:  initialize the cities array and print the cities
; input:    nothing
; output:   nothing (updates array and screen)
; destroys: nothing
;
cities_initialize	proc	near
	push	ax
	push	cx
	push	dx
	push	si

	lea	si, cities
	mov	cx, MAX_CITIES
	mov	dx, FIRST_CITY_LOCATION
	xor	ax, ax

init_loop:
	mov	HIT_COUNT[si], ax
	mov	LOCATION[si], dx
	add	dl, CITY_SPACING
	add	si, CITY_SIZE
	loop	init_loop

	pop	si
	pop	dx
	pop	cx
	pop	ax
	ret
cities_initialize	endp


;
; purpose:  draw the cities
; input:    nothing
; output:   nothing (screen is updated)
; destroys: nothing
;
cities_draw	proc	near
	push	cx
	push	si

	lea	si, cities
	mov	cx, MAX_CITIES

draw_loop:
	call	draw_city
	add	si, CITY_SIZE
	loop	draw_loop

	pop	si
	pop	cx
	ret
cities_draw	endp


;
; purpose:  draw a city 
; input:    si points to the city
; output:   nothing (screen is updated)
; destroys: nothing
;
draw_city	proc	near
	push	ax
	push	cx
	push	dx
	push	si

	mov	dx, LOCATION[si]
	mov	ax, HIT_COUNT[si]
	cmp	ax, MAX_HITS
	jle	alive
	lea	si, dead_city_image
	jmp	draw_it

alive:
	lea	si, city_image

draw_it:
	mov	cx, CITY_IMAGE_LENGTH
	call	image_draw
	add	dx, SCORE_DRAW_OFFSET
	call	screen_locate
	call	printAXhex

	pop	si
	pop	dx
	pop	cx
	pop	ax
	ret
draw_city	endp


;
; purpose:  check to see if a rock has hit any of the cities
; input:    dx = upper left corner of a rock
; output:   nothing (cities array and screen are updated)
; destroys: nothing
;
cities_hit_check	proc	near
	push	cx
	push	si

	lea	si, cities
	mov	cx, MAX_CITIES

check_loop:
	call	city_check_hit

	add	si, CITY_SIZE
	loop	check_loop

	pop	si
	pop	cx
	ret
cities_hit_check	endp


;
; purpose:  check to see if a rock has hit a city
; input:    dx = upper left corner of a rock, si points to a city, 
;           cl = rock image width
; output:   nothing (city array and screen are updated)
; destroys: nothing
;
city_check_hit	proc	near
	push	bx
	push	dx

	...

hit:
	...
	call	cities_draw
	
no_hit:	
	pop	dx
	pop	bx
	ret
city_check_hit	endp

code	ends
	end
