










FYI I am sending the solution to last years assignment 3 (64 bit multiply).

Just as your learn to write engligh by reading english, you can learn to 
write assembler by reading some.  

HAVE FUN
- dave


;
; product64.asm
;
; Solution to assignment 3
; CS366 
; Fall 1994
;
; This program computes the product of two 64 bit numbers read from the keyboard
;

MAX_READ_LENGTH	equ	  17D			; 16 digits + a return

CR		equ	  0dH
LF		equ	  0aH

TTY		equ	  10H
TTY_WRITE	equ	  0eH
TTY_CR		equ	0e0dH
TTY_LF		equ	0e0aH

DOS_SERVICE	equ	  21H			; dos services used follow
DOS_PRINT	equ	  09H
DOS_READ	equ	  0aH
DOS_TERMINATE	equ	  4cH
STATUS_OK	equ	   0			; used with DOS_TERMINATE

data		segment
product		dw	4 dup (?)		; 64 bit product
n1		dw	4 dup (?)		; 64 bit input number
n2		dw	4 dup (?)		; 64 bit input number
one_64_bits	dw	0,0,0,1
string		db	24 dup(?)		; input buffer
overflow_msg	db	'overflow', CR, LF, '$'
final_msg	db	'product is = $'
data		ends
  
stack	segment stack
	db 256 dup(?)
stack	ends


	extrn printAXhex:near
code	segment public byte 'code'
	assume cs:code, ds:data, ss:stack

main	proc
	mov  ax, seg data
	mov  ds, ax

	lea  di,n1				; read n1
        call read_number

	lea  di,n2				; read n2
        call read_number
	lea si,n1			 	; for debugging echo numbers
	call print_64
	lea si,n2
	call print_64

        lea  si,n1
        lea  bx,n2
        lea  di,product
        call multiply64				; [di] = [si] * [bx]

        lea  dx,final_msg
	mov  ah,DOS_PRINT
	int  DOS_SERVICE
        lea  si,product
	call print_64

	mov  ah,DOS_TERMINATE
	mov  al,STATUS_OK
	int  DOS_SERVICE
main	endp


;
; purpose:  64 bit addition
; input:    64 bit numbers pointed to by di, si
; output:   [di] := [di] + [si]
; destroys: nothing
;
add64	proc near
	push ax
	mov  ax,6[si]
	add  word ptr 6[di], ax
	mov  ax,4[si]
	adc  word ptr 4[di], ax
	mov  ax,2[si]
	adc  word ptr 2[di], ax
	mov  ax,0[si]
	adc  word ptr 0[di], ax
	jnc  ok

	push dx
	lea  dx,overflow_msg			
	mov  ah,DOS_PRINT
	int  DOS_SERVICE
	pop  dx
ok:
	pop  ax
	ret
add64	endp


;
; purpose:  convert ascii character representation of digit to hex representation
; input:    ascii character in al
; output:   hex digit in al
; destroys: nothing
;
convert_digit	proc near 	
	cmp  al,'9'
        jle  small2
        and  al,0dfH  				; [[ ask me ]]
	sub  al,'A' - 10D
        jmp  endif2
small2:
	sub  al,'0'
endif2:
        ret
convert_digit	endp


;
; purpose:  test if a 64 bit number is zero
; input:    si points to the number
; output:   zero flag set iff the input number is zero
; destroys: nothing
;
is_zero	proc near
        push ax
        xor  ax,ax
	cmp  ax,0[si]
	jnz  nz					; exit with zero bit clear
	cmp  ax,2[si]
	jnz  nz					; exit with zero bit clear
	cmp  ax,4[si]
	jnz  nz					; exit with zero bit clear
	cmp  ax,6[si]				; leaves zero bit correct

nz:	
	pop  ax
	ret
is_zero	endp


;
; purpose:  left shift a 64 bit number by 1 bit 
; input:    si points to the number
; output:   [si] = [si] shifted left 1 bit, 
;           carry flag set to bit shifted out
; destroys: nothing
;
left_shift64	proc near
	shl  word ptr 0[si], 1
	pushf					; save carry flag
	shl  word ptr 2[si], 1
	adc  word ptr 0[si], 0
	shl  word ptr 4[si], 1
	adc  word ptr 2[si], 0
	shl  word ptr 6[si], 1
	adc  word ptr 4[si], 0
	popf
	ret
left_shift64	endp


;
; purpose:  left shift a 64 bit number by n bits
; input:    si points to the number, cx contains n
; output:   [si] = [si] shifted n bits
; destroys: CX
;
left_shiftcx64	proc near
shift_loop:
        call left_shift64
	loop shift_loop
	ret
left_shiftcx64	endp


;
; purpose:  multiply two 64 bit numbers
; input:    si, bx point to the input numbers, 
;           di points the product's location 
; output:   [di] = [si] * [bx]
; destroys: AX
;
multiply64 proc near
   	push cx

        xor  cx,cx				; [[ fast mov cx,0 ]]
        mov  0[di], cx				; zero product
        mov  2[di], cx
        mov  4[di], cx
        mov  6[di], cx


multiply_loop:                                  

	test word ptr 6[si], 01                 ; if n1 is odd
; [[ test byte ptr uses 6 (not 7) why ? in test byte ptr 6[si], 01]]
	jz   even
	push si
	mov  si,bx                              ; si points to n2
	call add64
	pop  si                                 ; si back to n1

even:
	call right_shift64                      ; shifts number pointed to by si
	call is_zero				; stop when n1 == 0
	je   done
	push si
	mov  si,bx                              ; point si to n2
	call left_shift64                       ; shifts number pointed to by si
	pop  si
	jnc  multiply_loop
	
	push dx
	lea  dx,overflow_msg                    
	mov  ah,DOS_PRINT
	int  DOS_SERVICE   
	pop  dx
	jmp  multiply_loop

done:
	pop  cx
	ret
multiply64 endp


;
; purpose:  print a 64 bit number 
; input:    si points to the number 
; output:   nothing (number is printed to the screen)
; destroys: nothing
;
print_64	proc near
        push ax
	mov  ax,0[si]
	call printAXhex
	mov  ax,2[si]
	call printAXhex
	mov  ax,4[si]
	call printAXhex
	mov  ax,6[si]
	call printAXhex

	mov  ax,TTY_CR
	int  TTY
	mov  ax,TTY_LF
	int  TTY
	pop  ax
	ret
print_64	endp


;
; purpose:  read a 64 bit number 
; input:    di points to the location for the number 
; output:   [di] = the number read
; destroys: AX
;
read_number proc	near
        push si
        push dx

	lea  dx, string
	mov  byte ptr string,MAX_READ_LENGTH
	mov  ah, DOS_READ
	int  DOS_SERVICE

	lea  si,string+1			; convert string at [si]
	call string_to_number
 
        pop  dx
        pop  si
	ret
read_number endp


;
; purpose:  right shift a 64 bit number by 1 bit 
; input:    si points to the number 
; output:   [si] = [si] right shifted by 1 bit
; destroys: nothing
;
right_shift64	proc near
	shr  word ptr 6[si], 1
	shr  word ptr 4[si], 1
        jnc  rs1
        or   word ptr 6[si], 8000H
rs1:
	shr  word ptr 2[si], 1
        jnc  rs2
        or   word ptr 4[si], 8000H
rs2:
	shr  word ptr 0[si], 1
        jnc  rs3
        or   word ptr 2[si], 8000H
rs3:
	adc  word ptr 2[si], 0
	ret
right_shift64	endp


;
;
; purpose:  convert a string to a hex number 
; input:    si points to the string (first byte is the strings length), 
;           di points to the location to place the number 
; output:   [di] = the number in hex
; destroys: nothing
;
;
string_to_number	proc near
	push si
	push cx

	xor  cx,cx				; [[ fast mov cx,0 ]]
	mov  0[di],cx				; clear number
	mov  2[di],cx
	mov  4[di],cx
	mov  6[di],cx

        mov  cl,[si]				; get string length  (ch = zero)
	inc  si					; point past length

next_digit:
	lodsb
	call convert_digit
        push cx					; save digit count
        xchg si,di				; si->number (save si in di)
	mov  cx,4
	call left_shiftcx64			; shift number pointed to by si
        xchg si,di				; recover si and di
        pop  cx
	or   6[di], al				; or in new low nibble 
        loop next_digit
        
	pop  cx
	pop  si
	ret
string_to_number	endp

code	ends
	end main

