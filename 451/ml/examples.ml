(* 'cs451/ml/examples.ml' contains the following ML functions.
 * Also see the file 'cs451/ml/example.ml.run'.
 *)

fun add x y = x + y : int;
fun add2 (x,y) = x + y : int;

fun last lst = 
    if null lst then
	nil
    else
	let
	    val head::tail = lst 
	in
	    if null tail then
	        [head]
            else
	        last tail 
	end ;
fun length lst = 
    if null lst then
	0
    else
	1 + length (tl lst) ;
(* this is the length function written in ML using a "Scheme style" *)

(* now declare the length function in an "ML style" *)
fun length nil     = 0
  | length (x::xs) = 1 + length xs    (* notice that x is not used *)
  ;

(* or better yet (notice the "_" in the second line) *)
fun length nil     = 0
  | length (_::xs) = 1 + length xs
  ;

fun append nil     y = y
  | append (x::xs) y = x::append xs y
  ;

fun reverse nil     = nil
  | reverse (x::xs) = append (reverse xs) [x]
  ;

fun reverse2_helper nil     rsf = rsf
  | reverse2_helper (x::xs) rsf = reverse2_helper xs (x::rsf) 
  ;

fun reverse2 x = reverse2_helper x nil
  ;

fun map f nil = nil
  | map f (x::xs) = f x::map f xs
  ;
