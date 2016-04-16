From binkley Fri Dec  8 15:04:20 1995
Subject: writprot.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 15:04:16 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 1804      
Status: OR

; WRITE_PROT.ASM   (RUN as a COM)
          .radix 16

WRITE     equ   03
FORMAT    equ   05
DRIVE     equ   00                 ; the drive to be protected (0-3), A=0)
WRITE_PROT equ  03                 ; BIOS error code

code      segment
          assume cs:code, ds:code
          db    100 dup(?)
start:
          jmp   setin
newint:
          cmp   dl,DRIVE
          jne   skip                    ; not protected drive

          cmp   ah,WRITE                ; dissalow write and format
          je    set_error
          cmp   ah,FORMAT
          jne   skip

set_error:
          push  ds
          mov   ax,040                  ; bios data segment
          mov   ds,ax
          mov   ah,WRITE_PROT           ; set error code
          xor   al,al                   ; zero sectors transfered
          mov   DISK_STATUS,ah          ; save for status calls
          pop   ds
          stc                           ; set carry -> error
xyz       proc  far
          ret   2                       ; trash flags
xyz       endp

skip:
          db    0eaH                    ; define a far jmp to old int 13
off       dw    ?
segmnt    dw    ?


          assume ds:code
setin:
          mov   ax,cs
          mov   ds,ax

          mov   ax,3513                 ; get vector 13
          int   21
          mov   off, bx
          mov   segmnt, es              ; build jump instr

          lea   dx, newint
          mov   ax,2513                 ; set new int 13
          int   21

          mov   ax,3100
          lea   dx,setin+10             ; round odd segment up
          mov   cl,4
          shr   dx,cl                   ; convert to paragraphs
          int   21

          org   41
DISK_STATUS  db ?                       ; BIOS status holser

code      ends
          end   start

