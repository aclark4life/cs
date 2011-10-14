public	getch,outch,crlf,clear,outstr

outch 	movem.l	a0-a6/d1-d7,-(a7)
	move.b	#248,d7
	trap	#14
	movem.l	(a7)+,A0-A6/d1-d7
	rts

getch 	movem.l	a0-a6/d1-d7,-(a7)
	move.b #247
	trap	#14
	movem.l	(a7)+,a0-a6/d1-d7
	rts

crlf	movem.l	a0-a6/d1-d7,-(a7)
	lea 	$0,a5
	lea	$0,a6
	move.b	#227,d7
	trap	#14
	movem.l	(a7)+,a0-a6/d1-d7
	rts

clear	movem.l	a0-a6/d1-d7,-(a7)
	move.b	#248,d7
	move.b	#27,d0
	trap	#14
	move.b	#']',d0
	trap	#14
	move.b	#'2',d0
	trap	#14
	move.b	#'J',d0
	trap	#14
	movem.l	(a7)+,a0-a6/d1-d7
	rts

outstr	movem.l	a0-a6/d1-d7,-(a7)
loop	move.b	(a0)+,d0
	cmp.b	#0,d0	
	beq	done
	outch
	bra	loop
done	movem.l (a7)+,a0-a6/d1-d7
	rts

