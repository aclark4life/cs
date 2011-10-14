; add.asm

DOS_TERMINATE	EQU	4cH
DOS_PRINT	EQU	09H
DOS_SERVICE	EQU	21H
DOS_CHAR_WRITE	EQU	02H

mystack	segment	stack
	db	100 dup('stack')
mystack ends

data	segment
a	dw	9
b	dw	0bH
result	dw	?
a_is_message	db 'A = $'
b_is_message	db ' B = $'
result_is_message	db ' result = $'
hex_digits	db '0123456789ABCDEF'
data	ends


code	segment	public byte 'code'
	assume	cs:code
main	proc	near
	mov	ax, seg data
	mov	ds,ax
	assume	ds:data

	mov     dx, offset a_is_message
	mov	ah, DOS_PRINT
	int	DOS_SERVICE
	mov	ax,a
	call	printAXhex

	mov     dx, offset b_is_message
	mov	ah, DOS_PRINT
	int	DOS_SERVICE
	mov	ax,b
	call	printAXhex

	mov	ax,a
	mov	bx,b
	add	ax,bx
	mov	result,ax

	mov     dx, offset result_is_message
	mov	ah, DOS_PRINT
	int	DOS_SERVICE
 	mov	ax,result
	call	printAXhex

	mov	ah, DOS_TERMINATE
	int	DOS_SERVICE
main	endp


printAXhex	proc	near
	push	ax
	mov	al,ah
	call	printALhex
	pop	ax
	call	printALhex
	ret
printAXhex	endp

printALhex	proc	near
	push	di
	push	ax
	push	dx

	mov	di,ax
	shr	di,1		; low nibble
	shr	di,1
	shr	di,1
	shr	di,1
	add	di, offset hex_digits
	mov     dl,[di]
	push	ax			; save ax
	mov	ah, DOS_CHAR_WRITE
	int	DOS_SERVICE
	pop	ax

 	mov	di,ax
        and	di,000FH   
        add     di, offset hex_digits
	mov     dl,[di]
	mov	ah, DOS_CHAR_WRITE
	int	DOS_SERVICE

	pop	dx
	pop	ax
	pop	di
	ret

printALhex	endp
code	ends
	end
