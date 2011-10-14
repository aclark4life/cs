;  Jennifer Galvin
;
;
;
;

WRITE_CHAR		equ 09h
DOS_SERVICE 		equ 21h
data 	segment

message	db	'Hello World$'

data 	ends

code 	segment	public	byte	'code'
	assume cs:code

main	proc	near
	
	mov dx, offset message

	assume  ds:data
	mov ah, WRITE_CHAR 
	int DOS_SERVICE 


	mov 	ax,4c00H
	int 	21H



main endp

code	ends
	end
