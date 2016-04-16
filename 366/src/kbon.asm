From binkley Fri Dec  8 15:04:01 1995
Subject: kbon.asm
To: aclark (J. Alexander Clark), bduncan (Cousin Brucie), bwu (Bin Wu),
        bjubb (Brennan Jubb), colive (Christopher Olive), ghall (George Hall),
        kmcguire (Kelly McGuire), pmcgee (Patti McGee), rhaber (Ryan Haber),
        gfurr (Gwendolyn Furr), hliu@love, tbennett@love, awielgosz@loyola.edu,
        ddobisch@loyola.edu, dzaudtke@loyola.edu, kmetzler@loyola.edu,
        lhopkins@loyola.edu, nrusso@loyola.edu, mdubin@loyola.edu,
        rhemling@loyola.edu
Date: Fri, 8 Dec 1995 15:03:56 -0500 (EST)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 298       
Status: O

; KNON.ASM turns the keyboard on
         .radix 16
code     segment
         assume cs:code,ds:code

         in    al,21
         and   al,0fdH                  ; second bit is KB
         out   21,al
         mov   ah,4c
         int   21                      ; exit

code     ends
         end

