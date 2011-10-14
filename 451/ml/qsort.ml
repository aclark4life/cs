From binkley Wed Oct  9 14:36:16 1996
Subject: no subject (file transmission)
To: binkley (Dave Binkley), aclark (J. Alexander Clark),
        ddobisch (Dawn Dobisch), bduncan (Cousin Brucie), rhaber (Ryan Haber),
        ghall (Curious George), rhemling (Roland Hemling),
        bjubb (Brennan Jubb), kmcguire (Kelly McGuire),
        jmeehan (Janine Meehan), kmetzler (Kirsten Metzler),
        colive (Christopher Olive), nrusso (Nick Russo),
        awielgos (April Wielgosz), bwu (Bin Wu)
Date: Wed, 9 Oct 1996 14:36:11 -0400 (EDT)
X-Mailer: ELM [version 2.4 PL22]
Content-Type: text
Content-Length: 468       
Status: O



fun append nil ys = ys
  | append (x::xs) ys = x:: (append xs ys)
  ;


fun qs nil = nil
  | qs [x] = [x]
  | qs (pivot::l) = 
	  let  
	      fun ph pivot nil smalls bigs =
		     (append (qs smalls) (pivot :: (qs bigs)))
	        | ph (pivot:int) l   smalls bigs =
		     if pivot < hd l then
			 ph pivot (tl l) smalls (hd l :: bigs)
		     else
			 ph pivot (tl l) (hd l :: smalls) bigs
	      fun p pivot l = ph pivot l nil nil;
	 in 
	     p pivot l 
	end
  ;

