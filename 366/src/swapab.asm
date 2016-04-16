From binkley Fri Dec  8 15:04:11 1995
Subject: swapab.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 15:04:07 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 729       
Status: O

         .radix 16
code     segment
         assume cs:code,ds:code
         jmp   setin
newint:
         or    dl,dl                   ; set zero = 1
         jz    zero
         cmp   dl,01
         jne   exit
         xor   dl,dl                   ; set one = 0
         jmp   exit
zero:
         inc   dl                      ; set zero = 1
exit:
         db    0ea
off      dw    0
sgmnt    dw    0

setin:
         push  cs
         pop   ds
         mov   ax,3513                 ; get disk int
         int   21
         mov   off,bx
         mov   bx,es
         mov   sgmnt,bx

         lea   dx,newint
         mov   ax,2513
         int   21

         lea   dx,setin+100
         int   27

code     ends
         end

