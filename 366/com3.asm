From binkley Fri Dec  8 14:57:09 1995
Subject: com3.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 14:57:05 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 5225      
Status: O

; com3.ASM. My first device driver.
; A Bare Bones driver for COM3.  This driver supports only enough
; to get by, it performs the rs-232 functions to com1 however by
; changing com_port to 2 (com3) and adding supporting hardware
; a com3 could be realized.
; read_imm and flush_in have not been tested but the get char
; routine used by these functions.
; IOTCL is not supported.
         
         .radix 16
COM_NUMBER equ 0                       ; com1
TIME_OUT equ   80H
CTS      equ   01100000B               ; clear to send
RE_TRY_COUNT equ 10
CHAR_READY equ 00000001B
DONE     equ   0100
BUSY     equ   0200H
NOT_BUSY equ   0fdffH
END_OFF  equ   14D
END_SEG  equ   16D
DEST_OFF equ   14D
DEST_SEG equ   16D
COUNT    equ   18D                     ; length to transfer
STATUS   equ   3
NOERROR  equ   0100H                   ; for status
         
         
code     segment
         assume cs:code
; device driver for com3 (using com1 hardware)
; Header
         dd    -1
         dw    8000                    ; character no ioctl C000 for ioctl
         dw    offset strategy
         dw    offset interrupt
         db    'COM3    '              ; len must be eight
         
main     proc  far
         
functab  dw    offset init
         dw    offset nop
         dw    offset nop
         dw    offset nop              ; ioctl
         dw    offset read
         dw    offset read_imm
         dw    offset in_status
         dw    offset flush_in
         dw    offset write
         dw    offset write_v          ; verify
         dw    offset out_status
         dw    offset out_flush
         dw    offset nop              ; ioctl out
         
         dw    offset nop              ; insurance
rh_seg   dw    ?
rh_off   dw    ?
         
strategy: 
         mov   cs:rh_seg,es            ; request segment
         mov   cs:rh_off,bx            ; request offset
         ret
         
interrupt: 
         push  ax
         push  bx
         push  cx
         push  dx
         push  ds
         push  es
         push  si
         push  di
         mov   al,es:[bx+2]            ; function number
         xor   ah,ah                   ; convert to offset
         shl   ax,1
         lea   di,functab
         add   di,ax
         call  word ptr cs:[di]
         pop   di
         pop   si
         pop   es
         pop   ds
         pop   dx
         pop   cx
         pop   bx
         pop   ax
         ret
main     endp
         
read:    
         mov   di,es:[bx+DEST_OFF]     ; buffer addr
         mov   cx,es:word ptr [bx+COUNT]
         push  es
         mov   es,es:word ptr [bx+DEST_SEG]
get_loop: 
         call  get_char
         stosb                         ; save and inc di
         loop  get_loop
         pop   es
         or    es:word ptr [bx+STATUS],NOERROR
         ret
         
read_imm:                              ; get byte and stat leave byte in buff
         call  get_rs_stat             ; stat to ah char in al
         test  ah,CHAR_READY
         je    set_ready
         or    es:word ptr [bx+STATUS],BUSY ; no char
         ret
set_ready: 
	 call  get_byte
         mov   es:[bx+14D],al          ; return char to dos
         and   es:word ptr [bx+STATUS],NOT_BUSY ; clear bit
         ret
         
in_status: 
out_status: 
         or    es:word ptr [bx+STATUS],DONE
         ret
         
         
flush_in: ;    read till time out
         call  get_byte
         test  ah,TIME_OUT
         jnz   flush_in
         or    es:word ptr [bx+STATUS],DONE
         ret
         
out_flush: 
nop:     
         ret
write_v:                               ; same as a write
write:   
         mov   si,es:[bx+DEST_OFF]     ; buffer addr
         mov   ds,es:[bx+DEST_SEG]
         mov   cx,es:[bx+COUNT]
write_loop: 
         lodsb                         ; get each byte
         call  write_char
         loop  write_loop
         or    es:word ptr [bx+STATUS],NOERROR
         ret
         

get_char proc  near
         call  get_byte                ; call get byte until no time out
         test  ah,TIME_OUT
         jnz   get_char                ; live with other errors
         ret
get_char endp
         
         
get_byte proc  near
; get a single byte unless and error or time out occurs
         push  dx
         mov   ah,02                   ; get char
         mov   dx,COM_NUMBER
         int   14
         pop   dx
         ret
get_byte endp
         
         
write_char proc near
         push  cx
         push  dx
         mov   dx,COM_NUMBER
         mov   cx,RE_TRY_COUNT
send:    
         mov   ah,01                   ; write byte
         int   14
         test  ah,TIME_OUT
         loopnz send                   ; if other error return junk
         pop   dx
         pop   cx
         ret
write_char endp
         
get_rs_stat proc near
         push  dx
         mov   dx,COM_NUMBER
         mov   ah,03                   ; get info
         int   14
	 pop   dx
         ret
get_rs_stat endp
         
         
init:    
         mov   es:word ptr [bx+END_OFF],offset init       ; end addr
         mov   es:[bx+END_SEG],cs
         or    es:word ptr [bx+STATUS],NOERROR
         ret
         
code     ends
         end
         

