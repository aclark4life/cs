
; printhex.asm
;


TTY		equ	10H
TTY_WRITE	equ	0eH

        public printAXhex
code	segment public byte 'code'
	assume cs:code

; destroys AX
; 
printAXhex	proc	near
	push ax
	mov  al,ah
	call printALhex
	pop  ax
	call printAlhex
	ret
printAXhex	endp

; 
; destroys AX
;
printALhex	proc	near
	push ax
	shr  al,1
	shr  al,1
	shr  al,1
	shr  al,1
        call printNibble
	pop  ax
	and  al,0FH
	call printNibble
	ret
printALhex	endp

; 
; destroys AL
;
printNibble	proc	near
        cmp  al,10D
        jl   small
        add  al,'A' - 10D
        jmp  endif
small: 
        add  al,'0'
endif:
        mov  ah,TTY_WRITE
	int  TTY
	ret
printNibble	endp
code	ends
	end 









