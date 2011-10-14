(* aclark *)
datatype operation = plus | times | minus | lessthan ;
datatype variable = string_to_variable of string;
datatype exp = int_to_exp of int | variable_to_exp of variable |
	       exp_to_exp of operation * exp * exp;
datatype statement = assignment_statement of variable * exp | 
		     if_statement of exp * statement list * statement list | 
		     while_statement of exp * statement list;
datatype program = statement_list_to_program of statement list;     

    val sum = string_to_variable "sum";
    val i = string_to_variable "i";
    val a1 = assignment_statement (sum,(int_to_exp 0));
    val a2 = assignment_statement (i,(int_to_exp 1));
    val a3 = assignment_statement (sum,(exp_to_exp (plus,(variable_to_exp sum),
                                       (variable_to_exp i))));
    val a4 = assignment_statement (i,(exp_to_exp (plus,(variable_to_exp i),
                                                       (int_to_exp 1))));
    val e1 = exp_to_exp (lessthan,(variable_to_exp i),(int_to_exp 10));
    (* Program 1 computes i := 1 *)
    val Program1 = statement_list_to_program [a2];
    (* Program 1 computes the sum of 1,2,3,4,5,6,7,8,9 *)
    val Program2 = statement_list_to_program
                       [a1, a2, while_statement (e1, [a3, a4])];

fun apply (times,v1,v2) = v1*v2
  | apply (plus,v1,v2) = v1+v2
  | apply (minus,v1,v2) = v1-v2
  | apply (lessthan,v1,v2) = if v1 < v2 then 1 else 0; 

fun E (int_to_exp i) store = i 
    | E (variable_to_exp v) store = store v
    | E (exp_to_exp (opp,e1,e2)) store = 
    let
       val v1 = E e1 store
       val v2 = E e2 store
    in
       apply (opp,v1,v2)
    end;

fun SL [] store = store | SL (X::XS) store = 
	let
	fun S (assignment_statement(v,e)) store =
		(fn x => if x = v then (E e store) else store x) |
		S (if_statement(e,stT,stF)) store = 
		if (E e store) = 1 then SL stT store else SL stF store |
		S (while_statement(e,st)) store = if (E e store) = 1 then
		(S (while_statement(e,st)) (SL st store)) else
		store
	in
	   (SL XS (S X store))
	end;

fun initial_store x = 0;

fun eval (statement_list_to_program (p)) = SL p initial_store;
 
