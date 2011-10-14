; macros.h

exit	macro	status
	mov	al, status
	mov	ah, DOS_TERMINATE
	int	DOS_SERVICE
	endm

print	macro	string
	push	ax
	push	dx
	mov	ah, DOS_PRINT_STRING
	lea	dx, string
	int	DOS_SERVICE
	pop	dx
	pop	ax
	endm
