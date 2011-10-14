; sieve.scm
;
; computing primes using the sieve of Eratosthenes
;

(define nil ())

(define (mod a b) (remainder a b))


(define (sieve filter n)
    (cond ((> n 100)   ())
           ((filter n) (sieve filter (+ n 1)))
	   (else       (cons n (sieve (lambda (x) (if (eq? 0 (mod x n)) 
	                                              #T 
				                      (filter x)))
	                              (+ n 1))))
    )
)


(define false (lambda (a) ()))
(sieve false 2)
	     
	     
