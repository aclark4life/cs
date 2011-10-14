(*
 * 'cs451/ml/examples2.ml' contains the following ML examples
 * Also see the file 'cs451/ml/example.ml.run'.
 *)


fun length nil     = 0		(* repeat *)
  | length (_::xs) = 1 + length xs
  ;

fun length2_helper nil     rsf = rsf
  | length2_helper (x::xs) rsf = length2_helper xs 1+rsf
  ;

fun length2 x = length2_helper x 0
  ;

(* for problem 7.2  			(DO PART a FOR HOMEWORK) *)
(* problem 7.2c *)
fun factorial1 1 = 1
  | factorial1 n = n * factorial1 n-1
  ;

fun factorial_helper 1 rsf = rsf
  | factorial_helper n rsf = factorial_helper (n-1) n*rsf
  ;

fun factorial2 n = factorial_helper n 1
  ;

(*
 * ML (like Scheme) has first class functions.  Thus, functions are values just
 * like integers, booleans, etc.. For example, the following function converts
 * a binary function into a unary one by supplying one argument.  Note that 
 * this function takes a function as an argument and returns a function as its
 * result.
 *)

fun fix_first_argument bi_func constant argument = 
    let 
	val p = (constant, argument)
    in 
	bi_func p 
    end
  ;

fun addp (x,y) = x+y:int;

val increment = fix_first_argument addp 1 ; 

(* actually, because functions are curried, fix_first_argument is unnecessary.
 * For examples, try the following
 *)
val plus2 = add 2;

(* can you explain the difference between add and addp? *)
