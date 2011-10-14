
(* sieve.ml *)

(* computes primes using the sieve of Eratosthenes *)

fun multiple a b = b mod a = 0 
  ;

fun sieve filter 100 = nil
  | sieve filter n   = if filter n then
			   sieve filter (n+1)
		       else
			   let
			       fun new_filter x = if multiple n x then 
						      true
						  else
						      filter x
			   in
			       n::(sieve new_filter (n+1))
			   end
  ;

fun false_function x = false;	(* a starting place *)

sieve false_function 2;		(* test sieve *)



(* lazy lists (called sequences *)

datatype 'a seq = Nil | cons of 'a * (unit -> 'a seq) ;

exception head_Nil;
fun head Nil           = raise head_Nil
  | head (cons (x, f)) = x;

exception tail_Nil;
fun tail Nil           = raise tail_Nil
  | tail (cons (x, f)) = f();

fun from k = cons(k, fn()=>from (k+1));

(* collect n things from a sequence *)
fun takeq (0,x)           = []
  | takeq (n,Nil)         = []
  | takeq (n, cons(x,xf)) = x :: takeq(n-1, xf())
  ;

fun sieve_sequence filter (cons(100,A)) = nil
  | sieve_sequence filter inStream      = 
	if filter (head inStream) then
            sieve_sequence filter (tail inStream)
        else
            let
                fun new_filter x = 
		    if multiple (head inStream) x then 
                        true
                    else
                        filter x
            in
                (head inStream) :: (sieve_sequence new_filter (tail inStream))
            end
  ;

sieve_sequence false_function (from 2);   (* sieve sequence test *)

(* truly lazy prime caculator ! *)

fun sieve_stream filter inStream   = 
	if filter (head inStream) then
            sieve_stream filter (tail inStream)
        else
            let
                fun new_filter x = 
		    if multiple (head inStream) x then 
                        true
                    else
                        filter x
            in
                cons ((head inStream), fn()=>(sieve_stream new_filter (tail inStream)))
            end
  ;


val p = sieve_stream false_function (from 2);   (* "test" sieve stream *)

val p1 = sieve ff 2;
val p2 = sieve_sequence ff (from 2);
val p3 = takeq((length p2), p);
p1 = p2;
p1 = p3;

(* a sample run:
- use "sieve.ml";
[opening sieve.ml]
val multiple = fn : int -> int -> bool
val sieve = fn : (int -> bool) -> int -> int list
val false_function = fn : 'a -> bool
val it = [2,3,5,7,11,13,17,19,23,29,31,37,...] : int list
datatype 'a  seq
con Nil : 'a seq
con cons : 'a * (unit -> 'a seq) -> 'a seq
exception head_Nil
val head = fn : 'a seq -> 'a
exception tail_Nil
val tail = fn : 'a seq -> 'a seq
val from = fn : int -> int seq
val takeq = fn : int * 'a seq -> 'a list
val sieve_sequence = fn : (int -> bool) -> int seq -> int list
val it = [2,3,5,7,11,13,17,19,23,29,31,37,...] : int list
val sieve_stream = fn : (int -> bool) -> int seq -> int seq
val p = cons (2,fn) : int seq
val p1 = [2,3,5,7,11,13,17,19,23,29,31,37,...] : int list
val p2 = [2,3,5,7,11,13,17,19,23,29,31,37,...] : int list
val p3 = [2,3,5,7,11,13,17,19,23,29,31,37,...] : int list
val it = true : bool
val it = true : bool
[closing sieve.ml]
val it = () : unit
-

*)

