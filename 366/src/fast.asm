From binkley Fri Dec  8 15:03:50 1995
Subject: fast.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 15:03:45 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 3195      
Status: O

; FAST.ASM

; notes
; Might check scrolling on screen one might NOT.
; if it does then it cant print to other screens unless
; another parm is added (screen number)
; call would be (string,row,col,screen_number) 

; ASSUMES: Graphics board, Text window 0, Text mode,?
; NOTE other screens can be written to by giving a line number
; that would be "off" screen 1.  I think.
         .radix 16

;	define big or small model for library assembly code
FALSE	equ	0	;for small model
TRUE	equ	1	;for big model
@bigmodel equ false     ;select this for model desired

; prologue	11/5/83

;	standard prologue for c86 assembly code

;	DEFINE ARGUMENT BASE RELATIVE FROM BP

IF	@BIGMODEL
@AB	EQU	6
ELSE
@AB	EQU	4
ENDIF

@CODE	SEGMENT BYTE PUBLIC 'CODE'
@CODE	ENDS
@DATAB	SEGMENT PARA PUBLIC 'DATAB'
@DATAB	ENDS
@DATAC	SEGMENT BYTE PUBLIC 'DATAC'
@sb	label	byte
@sw	label	word
@DATAC	ENDS
@DATAI	SEGMENT BYTE PUBLIC 'DATAI'
@ib	label	byte
@iw	label	word
@DATAI	ENDS
@DATAT	SEGMENT BYTE PUBLIC 'DATAT'
@DATAT	ENDS
@DATAU	SEGMENT BYTE PUBLIC 'DATAU'
@ub	label	byte
@uw	label	word
@DATAU	ENDS
@DATAV	SEGMENT BYTE PUBLIC 'DATAV'
@DATAV	ENDS
DGROUP	GROUP	@DATAB,@DATAC,@DATAI,@DATAT,@DATAU,@DATAV
@CODE	SEGMENT BYTE PUBLIC 'CODE'
	ASSUME	CS:@CODE,DS:DGROUP

;	END OF PROLOGUE

colperrow equ 80D
crt_start equ  0B800

         public fastpr
fastpr   proc  near
         push  bp                      
	 mov   bp,sp                   ; stdandard entry
; Call syntax  fastpr(string,row,col) ;
; char *string ;
; int row,col ;
; string will be written to the location in row,col
; The BIOS cursor's position is unchanged
;
;
; First calulate start offset from row,col
         push  ax                      ; reg me some registers
	 push  bx
         push  dx
         push  di
         push  si
         push  es

         mov   ax,6[bp]                ; get row
         mov   bx,colperrow
         mul   bx
         add   ax,8[bp]                ; add column offset
         sal   ax,1                    ; *2 for attribute
	 mov   bx,crt_start            ; segment of vidio
	 mov   es,bx
	 mov   si,4[bp]                ; addr of data to print

	 cld                           ; set directrion flag
	 mov   dx,3daH          ; 8625 retrace reg.
	 mov   di,ax                   ; where to put data

lp:
	 call  retrace                 ; wait for vertical
	 mov   dx,3d8
	 mov   al, 0                   ; vidio off
	 out   dx,al

	 lodsb                         ; get char
	 or    al,al                   ; zero = EOS
	 jz    exit

	 stosb                         ; place on screen
	 inc   di                      ; skip attribute byte
	 jmp   lp                      ; repeat until NUL found

exit:
	 call  retrace                 ; wait for vertical
	 mov   al, 09H                 ; vid on, BW, 80x25 alphanum
	 out   dx,al
	 pop   es
         pop   si
         pop   di
         pop   dx
         pop   bx
         pop   ax
         pop   bp
         ret

retrace:
; trashes al, dx must have 6845 register (addr = 3DAH)
;        ret   ; reMOVE?????
         in    al,dx
         test  al,8                    ; wait for verticle retrace
         jz    retrace
         ret

fastpr   endp

@CODE	ENDS
         end

