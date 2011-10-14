;
; '~binkley/public_html/451/examples.scm' contains the following scheme functions.
; Also see the file '~binkley/public_html/451/scheme.output'.
;

(define nil '())   ; our version of scheme forgot to define 'nil'

(define add (lambda (a b) (+ a b)))   ; or "(define (add a b) (+ a b)"
(define sub (lambda (a b) (- a b)))   ; or "(define (sub a b) (- a b)"

(define (last list)
    (cond ((null? list) nil)
          ((null? (cdr list)) (car list))
	  (else (last (cdr list)))
    )
)

(define (length x)
    (cond ((null? x)  0)
          (else  (+ 1 (length (cdr x))))
    )
)

(define (append a b)
    (cond  ((null? a) b)
           (else (cons (car a) (append (cdr a) b)))
    )
)

(define (reverse x)
    (cond  ((null? x) nil)
           (else (append (reverse (cdr x)) (list (car x))))
    )
)

(define (reverse2-helper in out)
    (cond ((null? in) out)
          (else (reverse2-helper (cdr in) (cons (car in) out)))
    )
)

(define  (reverse2 x)
    (reverse2-helper x nil)
)

(define (map f list)
    (cond  ((null? list) nil)
           (else  (cons (f (car list)) (map f (cdr list))))
    )
)
