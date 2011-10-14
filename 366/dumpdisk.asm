From binkley Fri Dec  8 15:03:39 1995
Subject: dumpdisk.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 15:03:35 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 2980      
Status: O

         .radix 16
number_retries equ 2
code     segment
         assume cs:code,ds:code
         mov   ax,cs
         mov   ds,ax
         mov   es,ax

         mov   dx,0100                 ; check number of sides by 
         mov   cx,0001                 ; reading track zero sector 1
         call  get_sec                 ; read a sector
         jc    single
         mov   byte ptr sides,2
single:

; count the number of sectors per track (start at 8)
         xor   dx,dx                   ; drive A head 0
         mov   ch,0                    ; track
         mov   cl,max_sector
next:
         call  get_sec
         jc    found
         inc   cl
         jmp   next

found:
         mov   max_sector,cl


; print number sides, sectors
         mov   dl,sides
         add   dl,'0'
         mov   ah,02
         int   21
         mov   dl,max_sector
         add   dl,'0'-1
         mov   ah,02
         int   21

; loop through each sector, each track untill ^C
         xor   dx,dx
         mov   cx,0001                 ; (S0,T0,S1)

next_track:
next_sector:
         call  get_sec
         jc    error
         call  print_sec
skip:
         inc   cl
         cmp   cl,max_sector
         jl    next_sector

         inc   dh                      ; head inc
         cmp   dh,sides
         jge   nxt
         mov   cl,01                   ; back to sector one
         jmp   next_sector

nxt:
         inc   ch                      ; next track
         mov   cl,01                   ; back to sector
         mov   dh,0                    ; back to TOP
         jmp   next_track

error:

         push  dx
         lea   dx,errm
         mov   ah,09
         int   21
         pop   dx
         jmp   skip



get_sec:
         lea   bx,data
         mov   di,number_retries
re_try:
         mov   ax,0201                 ; read one
         int   13                      ; do read
         jnc   good
         xor   ax,ax                   ;re-set disk system
         int   13
         dec   di                      ; count of re-tries
         jz    bad_read
         jmp   re_try

bad_read:
         stc                           ; set carry
good:
         ret

print_sec:
         push  dx
         push  cx

         lea   si,data
         mov   cx,200                  ; 1 sector

print_loop:
         lodsb
         cmp   al,' '
         jge   ascii
         mov   al,'.'
;
ascii:
         mov   dl,al
         mov   ah,02                   ; print char
         int   21

lp:
         loop  print_loop
         mov   ah,01                   ; read a char (pause)
         int   21
         pop   cx

         pop   dx
         ret
         xor   dl,dl                   ; drive A
         mov   ah,4c
         int   21                      ; terminate

; data

flag     db    00
sides    db    1                       ; assume single
max_sector db  8
errm     db    'Cant read sector ',0dH,0aH,'$'

data     db    200 dup(?)
code     ends
         end


