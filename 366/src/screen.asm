; screen.asm

SET_MODE		equ	00H
SET_CURSOR_LOCATION	equ	02H
READ_CURSOR_LOCATION	equ	03H
SCROLL_WINDOW		equ	06H
READ_CHARACTER		equ	08H
WRITE_CHARACTER		equ	0AH
WRITE_DOT		equ	0CH
VIDEO_SERVICE		equ	10H

CLEAR_ALL_LINES		equ	00H
NORMAL_ATTRIBUTE	equ	07H
PAGE_NUMBER		equ	00H


	public	screen_set_mode
	public	screen_get_cursor_location
	public	screen_locate
	public	screen_read_char
	public	screen_write_char
	public	screen_clear_window
	public	screen_write_dot

code	segment public byte 'code'
	assume cs:code
;
; purpose:  set the screen mode 
; input:    al = mode (3 = 80x24 color, 6 = 640x200, others exist)
; output:   nothing (screen mode is change and screen is cleared)
; destroys: nothing
;
screen_set_mode	proc	near
	push	ax
	push	si
	push	di
	push	bp

	mov	ah, SET_MODE
	int	VIDEO_SERVICE

	pop	bp
	pop	di
	pop	si
	pop	ax
	ret
screen_set_mode	endp

	
;
; purpose:  get the cursors location
; input:    nothing
; output:   dx holds the location (dh=row, dl=column)
; destroys: nothing
;
screen_get_cursor_location	proc	near
	push	ax
	push	bx
	push	cx
	push	si
	push	di
	push	bp

	mov	bh, PAGE_NUMBER
	mov	ah, READ_CURSOR_LOCATION
	int	VIDEO_SERVICE

	pop	bp
	pop	di
	pop	si
	pop	cx
	pop	bx
	pop	ax
	ret
screen_get_cursor_location	endp


;
; purpose:  set the location of the cursor
; input:    dx holds the location dl=column, dh=row
; output:   nothing (the cursor is moved)
; destroys: nothing
;
screen_locate	proc	near
	push	ax
	push	bx
	push	cx
	push	si
	push	di
	push	bp

	mov	bh, PAGE_NUMBER
	mov	ah, SET_CURSOR_LOCATION
	int	VIDEO_SERVICE

	pop	bp
	pop	di
	pop	si
	pop	cx
	pop	bx
	pop	ax
	ret
screen_locate	endp


;
; purpose:  read the character at the current screen location
; input:    nothing
; output:   al = character at current cursor location
; destroys: nothing
;
screen_read_char	proc	near
	push	bx
	push	cx
	push	dx
	push	si
	push	di
	push	bp

	mov	bh, PAGE_NUMBER
	mov	ah, READ_CHARACTER
	int	VIDEO_SERVICE

	pop	bp
	pop	di
	pop	si
	pop	dx
	pop	cx
	pop	bx
	ret
screen_read_char	endp


;
; purpose:  write a character to the screen at the present curcor location
; input:    al holds the character
; output:   nothing (the screen is updated)
; destroys: nothing
;
screen_write_char	proc	near
	push	ax
	push	bx
	push	cx
	push	dx
	push	si
	push	di
	push	bp

	mov	bh, PAGE_NUMBER
	mov	cx,1	
	mov	ah, WRITE_CHARACTER
	int	VIDEO_SERVICE

	pop	bp
	pop	di
	pop	si
	pop	dx
	pop	cx
	pop	bx
	pop	ax
	ret
screen_write_char	endp

;
; purpose:  clear a window on the screen
; input:    ch,cl = upper left row, column, dh,dl = lower left row, column
; output:   nothing (affects screen)
; destroys: nothing
;
screen_clear_window	proc	near
	push	bx
	push	cx
	push	dx
	push	si
	push	di
	push	bp


	mov	bh, NORMAL_ATTRIBUTE
	mov	al, CLEAR_ALL_LINES
	mov	ah, SCROLL_WINDOW
	int	VIDEO_SERVICE

	pop	bp
	pop	di
	pop	si
	pop	dx
	pop	cx
	pop	bx
	ret
screen_clear_window	endp

;
; purpose:  write a dot
; input:    al = color value, dx = row, cx = column
;           (if al bit 7 is 1 then al bits 0-6 are xor'd with current value.)
; output:   nothing (affects screen)
; destroys: nothing
;
screen_write_dot	proc	near
	push	ax
	push	si
	push	di
	push	bp

	mov	ah, WRITE_DOT 
	int	VIDEO_SERVICE

	pop	bp
	pop	di
	pop	si
	pop	ax
	ret
screen_write_dot	endp
code	ends
	end
