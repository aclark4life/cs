        EXTERNAL        OUTCH
PIT     EQU             $FE8000
TCR     EQU             $21
CNTR    EQU             $25
TIVR    EQU             $23
TSR     EQU             $35

        ORG             $1000
INTRPT  ADD.B           #1,D1
        MOVE.B          #$A1,TCR(A0)
        MOVE.B          #$01,TSR(A0)
        MOVE.L          #$000009C4,D2
        MOVEP.L         D2,CNTR(A0)
        RTE

        ORG             $1500
START   MOVE.W          #$2700,SR
        LEA             PIT,A0
        MOVE.B          #64,D7
        MOVE.B          D7,TIVR(A0)
        MOVE.L          #INTRPT,D7
        MOVE.L          D7,$100

        MOVE.B          #$41,D0
        
        MOVE.B          #$A1,TCR(A0)
        MOVE.B          #$01,TSR(A0)
        MOVE.L          #$000009C4,D2
        MOVEP.L         D2,CNTR(A0)

        MOVE.W          #$2000,SR
        
LOOP_O  MOVE.B          #$00,D1

LOOP_T  CMP.B           #100,D1
        BNE             LOOP_T
        
        BSR             OUTCH
        ADD.B           #1,D0
        CMP.B           #$5B,D0
        BNE             LOOP_O
        
        WORD            $4AFB
        END             START
