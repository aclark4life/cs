From binkley Fri Dec  8 15:03:30 1995
Subject: binkdrv.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 15:03:26 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 5269      
Status: O

; DRV.ASM. My first device driver.
; A Bare Bones driver for COM3.  This driver supports only enough
; to get by, it preformes the rs-232 funtions to com1 howevev by
; changing comm_port to 2 (com3) and adding supporting hardware
; a bink: could be realized.
; read_imm and flush_in have not been tested but the get char
; routime used by these functions.
; IOTCL is not supported.
         
         .radix 16
comm_number equ 0                      ; com1
time_out equ   80H
cts      equ   01100000B               ; clear to send
re_try_count equ 10
char_ready equ 00000001B
done     equ   0100
busy     equ   0200H
not_busy equ   0fdffH
end_off  equ   14D
end_seg  equ   16D
dest_off equ   14D
dest_seg equ   16D
count    equ   18D                     ; length to transfer
status   equ   3
noerror  equ   0100H                   ; for status
         
         
code     segment
         assume cs:code
; device driver for bink thruogh com1
; Header
         dd    -1
         dw    8000                    ; character no ioctl C000 for ioctl
         dw    offset                  strategy
         dw    offset                  interupt
         db    'BINK    '              ; len must be eight
         
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
         
interupt: 
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
         mov   di,es:[bx+dest_off]     ; buffer addr
         mov   cx,es:word ptr [bx+count]
         push  es
         mov   es,es:word ptr [bx+dest_seg]
get_loop: 
         call  get_char
         stosb                         ; save and inc di
         loop  get_loop
         pop   es
         or    es:word ptr [bx+status],noerror
         ret
         
read_imm: ;    get byte and stat leave byte in buff
         call  get_rs_stat             ; stat to ah char in al
         test  ah,char_ready
         mov   es:[bx+14D],al          ; return char to dos
         je    set_ready
         or    es:word ptr [bx+status],busy ; no char
         ret
set_ready: 
         and   es:word ptr [bx+status],not_busy ; clear bit
         ret
         
in_status: 
out_status: 
         or    es:word ptr [bx+status],done
         ret
         
         
flush_in: ;    read till time out
         call  get_byte
         test  ah,time_out
         jnz   flush_in
         or    es:word ptr [bx+status],done
         ret
         
out_flush: 
nop:     
         ret
         
write_v:                               ; same as a write
write:   
         mov   si,es:[bx+dest_off]     ; buffer addr
         mov   ds,es:[bx+dest_seg]
         mov   cx,es:[bx+count]
write_loop: 
         lodsb                         ; get each byte
         call  write_char
         loop  write_loop
         or    es:word ptr [bx+status],noerror
         ret
         
;
; locate procedures
;
get_char proc  near
         call  get_byte                ; call get byte until no time out
         test  ah,time_out
         jnz   get_char                ; live with other errors
         ret
get_char endp
         
         
get_byte proc  near
; get a single byte unless and error or time out occures
         push  dx
         mov   ah,02                   ; get char
         mov   dx,comm_number
         int   14
         pop   dx
         ret
get_byte endp
         
         
write_char proc near
         push  cx
         push  dx
         mov   dx,comm_number
         mov   cx,re_try_count
send:    
         mov   ah,01                   ;write byte
         int   14
         test  ah,time_out
         loopnz send                   ; if other error return junk
         pop   dx
         pop   cx
         ret
write_char endp
         
get_rs_stat proc near
         push  dx
         mov   dx,comm_number
         mov   ah,03                   ; get info
         int   14
; ah has stat fanagle char into al
         ret
get_rs_stat endp
         
         
         
init:    
         mov   es:word ptr [bx+end_off],offset init ; end addr
         mov   es:[bx+end_seg],cs
         or    es:word ptr [bx+status],noerror
         ret
         
code     ends
         end
         

