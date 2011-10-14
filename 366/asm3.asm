From binkley Mon Oct 23 06:41:33 1995
Subject: no subject (file transmission)
To: aclark (J. Alexander Clark)
Date: Mon, 23 Oct 1995 06:41:32 -0400 (EDT)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 2922      
Status: OR

; assignment 3 part 1 
;
; this program adds hex number read from the keyboard until zero is entered.
; if a carry occurs it prints a message.
;

CR		equ	0dH
LF		equ	0aH

DOS_SERVICE	equ	21H
DOS_PRINT	equ	09H
DOS_READ	equ	0aH
DOS_TERMINATE	equ	4cH

MAX_READ_LENGTH	equ	 4

STATUS_OK	equ	 0


stack	segment	stack
	db	100 dup('stack');
stack	ends

data	segment	byte public
sum			dw   0
number_as_string	db   MAX_READ_LENGTH+1, 
actual_length		db   ?
buffer			db   MAX_READ_LENGTH+1 dup(?)
oops_carry_message	db   'Oops carry',CR,LF,'$'
byebye_message		db   'Bye now!',CR,LF,'$'
crlf_message		db   CR,LF,'$'
data	ends

	extrn	printAXhex:near

code	segment public byte 'code'
	assume 	cs:code, ds:data, ss:stack
	
main	proc	near
	mov	ax,seg data
	mov	ds,ax

loop:
        call	read_number
	or	ax,ax
	jz	done

	add	sum,ax
	jnc	print_number

	lea	dx,oops_carry_message
	mov	ah, DOS_PRINT
	int	DOS_SERVICE	

print_number:
	mov	ax,sum
	call	printAXhex
	lea	dx,crlf_message
	mov	ah,DOS_PRINT
	int	DOS_SERVICE
	jmp 	loop

done:
	lea	dx,byebye_message
	mov	ah, DOS_PRINT
	int	DOS_SERVICE
	mov	ah, DOS_TERMINATE
	mov	al, STATUS_OK
	int	DOS_SERVICE
main	endp

;
; purpose:  read a hex number from the keyboard
; input:    nothing (the number is read from the keyboard)
; output:   the number in AX
; destroys: nothing
;
read_number	proc	near
	push	di
	push	si

	lea	dx,number_as_string
	call	read_string

	lea	si,actual_length
	call	string_to_number  		; convert from [si] to AX

	pop	si
	pop	di
	ret
read_number	endp



;
; purpose:  convert ascii character representation of digit to hex representation
; input:    ascii character in al
; output:   hex digit in al
; destroys: nothing
;
convert_digit	proc near 	
	cmp	al,'9'
        jle	small2
        and	al,0dfH  			; [[ ask me ]]
	sub	al,'A' - 10D
        jmp	endif2
small2:
	sub	al,'0'
endif2:
        ret
convert_digit	endp


;
; purpose:  read a 16 bit number as a string
; input:    dx points to the string in dos read format
; output:   [dx] = contains the string read in
; destroys: nothing
;
read_string proc	near
	push	ax
        push	dx

	mov	ah, DOS_READ
	int	DOS_SERVICE

        pop	dx
	pop	ax
	ret
read_string endp


;
; purpose:  convert a string to a hex number 
; input:    si points to the string (first byte is the strings length,
;           which number be <= 4)
; output:   hex number in AX  
; destroys: nothing
;
string_to_number	proc near
	push	si
	push	cx
	push	bx

        mov	cl,[si]				; get string length 
	xor	ch,ch				; unsigned convert cl to cx
	inc	si				; point past length
	xor	bx,bx				; [[ fast zero BX ]]

next_digit:
        push	cx				; save digit count
	mov 	cl,4				; compute number * 16
	shl 	bx,cl				; (makes room for next digit)
        pop 	cx
	lodsb
	call	convert_digit
	or  	bl, al				; or in new low nibble 
        loop	next_digit
        
	mov	ax,bx
	pop	bx
	pop 	cx
	pop 	si
	ret
string_to_number	endp

code	ends
	end 	main

From binkley Mon Oct 23 06:41:43 1995
Subject: no subject (file transmission)
To: aclark (J. Alexander Clark)
Date: Mon, 23 Oct 1995 06:41:42 -0400 (EDT)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 3624      
Status: OR

; assignment 3 part 2
;
; this program adds hex number read from the keyboard until zero is entered.
; if a overflow or underflow occurs it prints a message.
;

CR	equ	0dH
LF	equ	0aH

DOS_SERVICE	equ	21H
DOS_PRINT	equ	09H
DOS_READ	equ	0aH
DOS_TERMINATE	equ	4cH

MAX_READ_LENGTH	equ	 5
STATUS_OK	equ	 0


stack	segment	stack
	db	100 dup('stack')
stack	ends

data	segment	byte public
sum			dw   0
number_as_string        db   MAX_READ_LENGTH+1,
actual_length           db   ?
buffer                  db   MAX_READ_LENGTH+1 dup(?)

oops_overflow_message	db   'Oops overflow',CR,LF,'$'
oops_underflow_message	db   'Oops underflow',CR,LF,'$'
byebye_message		db   'Bye now!',CR,LF,'$'
crlf_message		db   CR,LF,'$'
data	ends

	extrn	printAXhex:near

code	segment public byte 'code'
	assume  cs:code, ds:data, ss:stack
	
main	proc	near
	mov	ax,seg data
	mov	ds,ax

loop:
        call	read_number
	or	ax,ax
	jz	done

	add	sum,ax
	jno	print_number			; jmp no overflow

        js 	overflow			; pos + pos results in neg 
						; sign bit on = neg number

	lea	dx,oops_underflow_message
	jmp	print_message

overflow:
	lea	dx,oops_overflow_message
print_message:
	mov	ah, DOS_PRINT
	int	DOS_SERVICE	

print_number:
	mov	ax,sum
	call	printAXhex
	lea	dx,crlf_message
	mov	ah,DOS_PRINT
	int	DOS_SERVICE
	jmp 	loop

done:
	lea	dx,byebye_message
	mov	ah, DOS_PRINT
	int	DOS_SERVICE
	mov	ah, DOS_TERMINATE
	mov	al, STATUS_OK
	int	DOS_SERVICE
main	endp

;
; purpose:  read a hex number from the keyboard
; input:    nothing (the number is read from the keyboard)
; output:   the number in AX
; destroys: nothing
;
read_number	proc	near
	push	di
	push	si

	lea	dx,number_as_string
	call	read_string

	lea	si,number_as_string+1
	call	string_to_number  		; convert from [si] to AX

	pop	si
	pop	di
	ret
read_number	endp



;
; purpose:  convert ascii character representation of digit to hex representation
; input:    ascii character in al
; output:   hex digit in al
; destroys: nothing
;
convert_digit	proc near 	
	cmp	al,'9'
        jle	small2
        and	al,0dfH  			; [[ ask me ]]
	sub	al,'A' - 10D
        jmp	endif2
small2:
	sub	al,'0'
endif2:
        ret
convert_digit	endp


;
; purpose:  read a 16 bit number as a string
; input:    dx points to the string in dos read format
; output:   [dx] = contains the string read in
; destroys: nothing
;
read_string proc	near
	push	ax
        push	dx

	mov 	ah, DOS_READ
	int 	DOS_SERVICE

        pop	dx
	pop	ax
	ret
read_string endp


;
; purpose:  convert a string to a hex number 
; input:    si points to the string (first byte is the strings length,
;           which number be <= 4)
; output:   hex number in AX  
; destroys: nothing
;
; should check the a 5 digit number is not entered
;
string_to_number	proc near
	push	bx
	push	cx
	push	dx
	push	si

        mov 	cl,[si]				; get string length 
	xor 	ch,ch				; unsigned convert cl to cx
	inc 	si				; point past length
	xor 	bx,bx				; [[ fast zero AX ]]

	mov	dx,1				; flag for positive
        cmp 	byte ptr [si], '-'		; leading minus sign
	jne	positive
	mov	dx,-1				; flag for negative
	inc	si				; skip sign
	dec	cl
	jmp	next_digit

positive:
	cmp	cl,4
	jle	next_digit
	mov	cl,4				; limit positive number to 4 digits

next_digit:
        push	cx				; save digit count
	mov 	cl,4				; compute number * 16
	shl 	bx,cl				; (makes room for next digit)
        pop 	cx
	lodsb
	call	convert_digit
	or  	bl, al				; or in new low nibble 
        loop	next_digit
        
	mov	ax,bx
	cmp	dx,-1				; change sign?
	jne	no
	neg	ax				; 2's comp!
no:	
	pop 	si
	pop	dx
	pop 	cx
	pop	bx
	ret
string_to_number	endp

code	ends
	end 	main

