From binkley Fri Dec  8 15:04:16 1995
Subject: trapint.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 15:04:11 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 5814      
Status: O

     .radix 16
true     equ   01
false    equ   00


code segment
     assume ds:code,cs:code
         jmp   start
newint:
         cmp   byte ptr cs:active,false
         jne   useme
         jmp   ignore
useme:

         mov   cs:sp_sav,sp
         push  ss
         push  es
         push  ds
         push  di
         push  si
         push  bp
         push  sp_sav
         push  dx
         push  cx
         push  bx
         push  ax

         mov   ax,cs                   ; mov ds,cs
         mov   ds,ax

         mov   byte ptr active,false         ; dont debug me
	 mov   ax,withregs             ; which registers get printed

         mov   bp,sp                   ; first reg stored at
	 lea   di,regnames             ; printed names
         mov   cx,0eH                  ; number of regs + flags

lp:
	 mov   dx,1                    ; test if this reg should be printed
         shl   dx,cl
         test  ax,dx                   ; text one bit
         jz    next
	 call  print

next:
         inc   bp
	 inc   bp                      ; point to start of next #
         inc   di
         inc   di
         loop  lp                      ; repaet for all regs

         test  al,01                   ; need crlf ?
         jz    nocr
         lea   dx,crlf
	 call  printit
nocr:


	 pop   ax
         pop   bx
         pop   cx
         pop   dx
         pop   bp                      ; throw away sp_sav
         pop   bp
         pop   si
         pop   di
         pop   ds
         pop   es
         pop   ss                      ; token ss never changed
  
;        mov   sp,sp_sav               ; force correct stack

         mov   byte ptr cs:active,true          ; re-activate
ignore:

         db    0ea                     ; for jmp far
off      dw    0
segmnt   dw    0


print:
         push  ax
         mov   ax,[di]
	 mov   word ptr namereg,ax              ; register name
	 lea   dx,namereg              ; print 'ax=$'
	 call  printit

	 mov   bx,[bp]                 ; value to print
	 mov   dl,bh                   ; hi nibble BH
	 call  shift_prn
	 mov   dl,bh                   ; low nibble BH
	 call  prn
	 mov   dl,bl                   ; hi nibble BL
	 call  shift_prn
	 mov   dl,bl                   ; low nibble BL
	 call  prn
	 lea   dx,blank             ; print a blank
	 call  printit
	 pop   ax
	 ret


shift_prn:
	 shr   dl,1
	 shr   dl,1
	 shr   dl,1
	 shr   dl,1
prn:
	 and   dl,0f                   ; wanted nibble
	 add   dl,30H                  ; up to diget level
	 cmp   dl,3AH                  ; letter (a-f)
	 jl    no
	 add   dl,7                    ; adjust for letter
no:
	 call print_char
	 ret

withregs dw  ?
sp_sav   dw    ?
namereg  db    '12=$'            ; 0,0,'= $'
active   db  true
crlf     db    0aH,0dH,'$'
regnames dw 'XA','XB','XC','XD','PS','PB','IS','ID','SD','SE','SS','PI','SC','lF'
blank    db    ' $'
printit:
;        mov   ah,09 ; for screen (console)
;        int   21
;        ret

	 push  si
	 mov   si,dx                   ; source
printlp:
	 lodsb
	 cmp   al,'$'                  ; stop at $
	 je    eos
	 mov   ah,0e                   ; tty write
	 int   10
	 jmp   printlp
eos:
	 pop   si
	 ret


print_char:                            ; char in dl
	 push  dx
	 push  ax
	 mov   al,dl
	 mov   ah,0e                ; tty write
	 int   10
	 pop   ax
	 pop   dx
	 ret


start:
         push  cs
         pop   ds

         lea   dx,msg1                 ; whar to trace
         mov   ah,09
	 int   21                      ; print prompt
         lea   dx,buff
         mov   ah,0aH                  ; buffered input
	 int   21                      ; get vec number
         mov   ax,word ptr buff+2      ; both hi & low bytes
         xchg  ah,al                   ; correct diget order
         cmp   ah,3aH                  ; below = diget above = letter
         jl    diget
         add   ah,9                    ; adjust for letter
diget:
         mov   cl,4                    ; four bytes
         shl   ah,cl                   ; keep lower nibble
         cmp   al,3aH                  ; repeat for lower byte
         jl    diget2
         add   al,9
diget2:
         and   al,0f
         add   al,ah                   ; complete number in al
         push  ax                      ; save number
	 mov   ah,35                   ; dos get int
	 int   21
         mov   off,bx                  ; build jmp far instruction
         mov   bx,es
         mov   segmnt,bx

         lea   dx,msg2                 ; enter regs to be displayed
         mov   ah,09                   ; display msg
	 int   21

; display order will be ax,bx,cx,dx,sp,bp,si,di,ds,es,ss,cs,ip,flags

         mov   cx,0eH
         lea   bx,regnames             ; two bytes each
	 xor   di,di

loop:
         mov   dx,[bx]                 ; mov value thru dx
         mov   word ptr regname,dx
         lea   dx,msg3                 ; quear each one
	 mov   ah,09                   ; dos print
	 int   21

         mov   ah,01                   ; get char
	 int   21
         rcr   al,1                    ; hold bit in carry 
	 rcl   di,1                    ; build bit string into di
         inc   bx
         inc   bx
         loop  loop

         shl   di,1                    ; make even
	 mov   withregs,di             ; save value



         pop   ax                      ; recover vector number
	 lea   dx,newint               ; ds already set
	 mov   ah,25                   ; dos set int vector
	 int   21
         lea   dx,start+101
	 int   27                      ; leave process resident


msg1 db 'enter vector to be intercepted (two hex digets ex.09)$'
msg2 db 0aH,'For each register type 1 to display it 0 not to display $'

msg3 db 0dH,0aH,'Display register '
regname  dw  ?
     db ' ? $'
buff db 03,0,0,0,0

code     ends
	 end

