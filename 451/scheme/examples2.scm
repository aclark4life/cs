;
; '~binkley/public_html/451/examples2.scm' contains the following scheme examples
; Also see the file '~binkley/public_html/451/scheme.output'.
;
(define nil '())   ; our version of scheme forgot to define 'nil'

(define (length1 lst)			; a repeat
    (cond ((null? lst) 0)
	  (else (+ 1 (length1 (cdr lst))))
    )
)

;
; for problem 7.2  			(DO PART a FOR HOMEWORK)
;
(define (length2 list result-so-far)
    (cond  ((null? list) result-so-far)
           (else (length2 (cdr list) (+ 1 result-so-far)))
    )
)

;
; problem 7.2c
;
(define (factorial1 n)			; linear recursive version
    (cond ((eq? n 1) 1)
	  (else (* n (factorial1 (- n 1))))
    )
)

(define (factorial-helper n result)	; tail recursive version (helper)
    (cond ((eq? n 0) result)
          (else (factorial-helper (- n 1) (* result n)))
    )
)

(define (factorial2 x)			; tail recursive version
    (factorial-helper x 1)
)

;
; Scheme has First Class Functions.  Thus, function are values just like
; integers, booleans, etc.. For example, the following function converts a
; binary function into a unary one by supplying one argument.  Note that this
; function takes a function as an argument and returns a function as its result.
;
(define (fix-first-argument bi-func constant)
    (lambda (x) (bi-func constant x))
)

;
; For example, fix-first-argument is to define the function increment from 
; the function +.
;
(define increment (fix-first-argument + 1))

;
; Yet another factorial.  Unlike the other two this version produce a function
; that computes the answer, rather than computing an integer value.
;
(define (fact n)
    (cond  ((eq? n 1) 1)
	   (else (list '* n (fact (- n 1))))
    )
)
