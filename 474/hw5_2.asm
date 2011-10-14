* Homework set 5 #2
* Alex Clark

	ORG     $1000
START   EXTERNAL        OUTCH,GETCH,CRLF,CLEAR,OUTSTR
ENTER   BYTE            'PLEASE TYPE IN YOUR NAME: '
ENTER_E BYTE            0
GOOD    BYTE            'GOOD MORNING '
GOOD_E  BYTE            0
BAD     BYTE            ',THIS IS YOUR 68000 COMPUTER RESPONDING.'
BAD_E   BYTE            0
NAME    DS              48
	ORG             $5000
	LEA             ENTER,A0
	BSR             OUTSTR
	LEA             NAME,A1
LOOP    BSR             GETCH
	CMP.B           #$0D,D0
	BEQ             DONE
	MOVE.B          D0,(A1)+
	BRA             LOOP

DONE    BSR             CLEAR
	LEA             GOOD,A0
	BSR             OUTSTR
	LEA             NAME,A0
	BSR             OUTSTR
	LEA             BAD,A0
	BSR             OUTSTR
	BSR             CRLF
	WORD            $4AFB
	END             START

