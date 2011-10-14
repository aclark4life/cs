        EXTERNAL OUTCH
PIT     EQU      $FE8000        parallel interface & timer
PGCR    EQU      $01 		port general control register                     
PACR    EQU      $0D		port A control register
PADDR   EQU      $05		port A data direction register
PADR    EQU      $11		port A data register
        ORG      $1000
TABLE   BYTE     'D','3',$18,'7','A','0','8','4','B','1','9','5','C','2',$0D,'6'

        ORG      $1500
START   LEA      PIT,A0
        MOVE.B   #$00,PGCR(A0)	select mode 0          
        MOVE.B   #$80,PACR(A0)	select mode 0     	
        MOVE.B   #$0F,PADDR(A0) 0 selects 4 input bits, F sel 4 out bits

        MOVE.B   #%01110111,D4  initialize rotating zeros
LOOP    ROL.B    #1,D4		rotate a bit left     
        MOVE.B   D4,PADR(A0)	send 01110111 to the output of padr
        MOVE.B   PADR(A0),D5	put input from the padr to d5   
        MOVE.B   D5,D6          copy d5 to d6	
        NOT.B    D5		input is usually all 1's;
				* if a key is pressed,
				* THERE WILl be a zero in the input
				* to the padr
				* so if no key is pressed, make
				* 11111111 into 00000000			
        AND.B    #$F0,D5  	compare 11110000 with 00000000 (if no
				* key is pressed ) and get 
				* 
        CMP.B    #$00,D5	compare 00000000 with 
        BEQ      LOOP
                 
        MOVE.B   #0,D3
        NOT.B    D6
        AND.B    #$0F,D6
                 
ONE     CMP.B    #$02,D6
        BNE      TWO
        ADD.B    #1,D3
TWO     CMP.B    #$04,D6
        BNE      THREE
        ADD.B    #2,D3
THREE   CMP.B    #$08,D6
        BNE      FOUR
        ADD.B    #3,D3
FOUR    CMP.B    #$20,D5
        BNE      EIGHT
        ADD.B    #4,D3
EIGHT   CMP.B    #$40,D5
        BNE      TWELVE
        ADD.B    #8,D3
TWELVE  CMP.B    #$80,D5
        BNE      ZERO
        ADD.B    #12,D3

ZERO    LEA      TABLE,A5
        MOVE.B   (A5,D3.W),D0
        BSR      OUTCH

LETGO   MOVE.B   PADR(A0),D5
        NOT.B    D5
        AND.B    #$F0,D5
        CMP.B    #$00,D5
        BNE      LETGO

        CMP.B    #$18,D0
        BNE      LOOP

        WORD     $4AFB
        END      START

