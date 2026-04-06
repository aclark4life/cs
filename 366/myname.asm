
; I added the variable   attribute_table.
; see if you can get it to print using the attributes in attribute_table
; rather than the random ones.

; - dave




; print my name

CURSOR_POSITION    	equ   02H
INITIAL_ROW_COLUMN	equ   0303H
VIDEO_SERVICE   	equ   10H
WRITE_CHAR 		equ   09H
DOS_TERMINATE 		equ   4cH
DOS_SERVICE   		equ   21H



data	segment
myname		db	'dave!'
name_length	equ	$-myname
;attribute_table	db	4,5,6,7,0F
data 	ends

code	segment byte public 'code'
	assume cs:code

main	proc	near
	mov	ax,seg data
	mov	ds,ax
	assume  ds:data
        cld
	mov	di,56a3H		; starting adress for atributes

	mov	cx,10			; outter loop 10 times
	mov	dx,INITIAL_ROW_COLUMN

outter:
	push	cx
	mov	cx,name_length

        lea	si, myname
inner:
        ; locate cursor and print char

        mov	ah,CURSOR_POSITION
	inc	dl
	mov	bh,0
	int	VIDEO_SERVICE

        ;mov     al, [si]    ; al = *si++
	;inc	si
	lodsb			; al = *si++
; lodsb is the same as mov followed by inc (when direction flag is clear (cld))

	mov	ah, WRITE_CHAR
	push	cx
	mov	cx,1			; number of times char in al is printed

	mov	bl,[di]			; note di points to random address
	inc     di			; therefore this get a random byte

	int	VIDEO_SERVICE
	pop	cx

	loop 	inner
	pop	cx			; end of inner loop
	inc	dh
	mov	dl,dh

	loop	outter

	mov	ah,DOS_TERMINATE
	int	DOS_SERVICE
main	endp

code	ends
	end
