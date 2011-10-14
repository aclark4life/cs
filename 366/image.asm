; image.asm

	public	image_draw
	include	dos.h
	include	screen.h

code	segment	byte public 'code'
	assume cs:code

;
; purpose: draw an image 
; input: dx has the upper left corner's location, si points to the image
;        cx has image's length
; output: nothing (as a side effect the screen is updated)
; destroys: nothing! (called during interrupt)
;
; note: during interrupt can't call dos; therefore prints with int 10
;
image_draw	proc	near
	push	ax
	push	bx
	push	cx
	push	dx
	push	si

	mov	bx, dx			; save corner
	cld

image_loop:
	mov	dx, bx
	add	dx, [si]
	add	si, 2
	call	screen_locate
	lodsb
	call	screen_write_char
	loop	image_loop

	pop	si
	pop	dx
	pop	cx
	pop	bx
	pop	ax
	ret
image_draw	endp
code	ends
	end







;
; link with:
;          link rocks+shield+cities+image+screen+random+printhex;
;
