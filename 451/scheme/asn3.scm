


;  i was working on this and when i ran it i don't 
;  think it did what it was supposed to. can you take
;  a look


  (define (add a b) (+ a b))
  (define (sub a b) (- a b))
  (define (mul a b) (* a b))
  (define (div a b) (/ a b))

  (define (postfix list stack)
	(cond 
	((null? list) (car stack))
	((eq? (car list) '+) (postfix (cdr list) (cons (add (car stack) (car(cdr stack))) (cdr(cdr(stack))) )))   
	((eq? (car list) '-) (postfix (cdr list) (cons (sub (car stack) (car(cdr stack))) (cdr(cdr(stack))))))
	((eq? (car list) '*) (postfix (cdr list) (cons (mul (car stack) (car(cdr stack))) (cdr(cdr(stack))))))
	((eq? (car list) '/) (postfix (cdr list) (cons (div (car stack) (car(cdr stack))) (cdr(cdr(stack))))))
	(else (postfix (cdr list) (cons (car list) stack)))
	)
)

