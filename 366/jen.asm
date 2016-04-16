
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
	mov	ah,DOS_TERMINATE
	int	DOS_SERVICE
main	endp

code	ends
	end
