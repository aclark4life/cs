From binkley Fri Dec  8 15:03:33 1995
Subject: blkdrv.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 15:03:30 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 1445      
Status: O

; A device driver to give four dummy block devices.  This provides
; an environment similar to the lab (jet drive is drive g:).
; All request to the driver return a not ready error.
; should be converted to .com format (with exe2bin)
; and invoked through config.sys by "device = dummydrv.bin"

         .radix 16

code     segment
         assume cs:code
         dw    -1
         dw    -1
         dw    2000
         dw    offset str
         dw    offset int
         db    3                             ; number of units
	 db    7 dup (?)		     ; reserved for dos

int:
         cmp   byte ptr es:[bx+2],0          ; init only valid command
         je    init
         mov   word ptr es:[bx+3],8102       ; device not ready
	 jmp   exit

bpb      dw    512d
         db    1
         dw    1
         db    2
         dw    64d
         dw    360d
         db    0fch
         dw    2

bpb_ptr  dw    bpb
         dw    bpb                           ; one per device
         dw    bpb
         dw    bpb
exit:
str:
xyzzy    proc  far
         ret                                 ; a far return
xyzzy    endp


init:
         mov   byte ptr es:[bx+13d],3        ; number of units
         mov   word ptr es:[bx+14d],offset init
         mov   word ptr es:[bx+16d],cs
         mov   word ptr es:[bx+18d],offset bpb_ptr
         mov   word ptr es:[bx+20d],cs
         mov   word ptr es:[bx+3],0100
	 jmp   exit


code     ends
         end

