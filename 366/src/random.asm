; random.asm

	public	random

code	segment	public byte 'code'
	assume  cs:code

X		equ	19			; X,K used in seed=seed * X + K
K		equ	113
INITIAL_SEED	equ	567


; random - return an random number between 1 and N (N must be >= 1)
;
; input: ax = N
; output: ax = random number
; destroys: nothing
;
random	proc	near
	push	bx
	push	dx
	push	es

	cmp	ax,1				; N must be positive
	jge	ok
	mov	ax,1				; force N to positive number
ok:
	mov	bx,ax				; save N

	mov	ax,seg random_data		; establish addressing 
	mov	es,ax				; for random's data
	assume	es:random_data

	mov	ax,X				; seed = seed * X + K
	mul	es:seed
	add	ax,K
	mov	es:seed,ax

	xor	dx,dx				; return (seed mod N + 1)
	div	bx
	inc	dx
	mov	ax,dx
	
	pop	es
	pop	dx
	pop	bx
	ret
random	endp

code	ends


random_data	segment
bad_random   db   'Bad random input = $'
seed	dw	INITIAL_SEED
random_data	ends

	end 
