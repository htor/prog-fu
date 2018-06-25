(define (assert-equal val1 val2)
    (unless (equal? val1 val2)
        (displayln (list "assert error:" val1 "!=" val2))
        (exit 1)))

(define (list-length lst)
    (if (empty? lst)
        0
        (+ 1 (list-length (cdr lst)))))

(define (list-append lst1 lst2)
    (if (empty? lst1)
        lst2
        (cons (car lst1)
              (list-append (cdr lst1) lst2))))

(define (list-reverse lst)
    (if (empty? lst) 
        lst
        (list-append (list-reverse (cdr lst))
                     (list (car lst)))))

(define (list-flatten lst)
    (cond
        ((empty? lst) lst)
        ((list? (car lst))
            (list-append (list-flatten (car lst))
                         (list-flatten (cdr lst))))
        (else
            (cons (car lst)
                  (list-flatten (cdr lst))))))
          
                        
(assert-equal 0 (list-length '()))
(assert-equal 3 (list-length '(a b c)))
(assert-equal 3 (list-length (cons 1 (list 2 3))))

(assert-equal '() (list-append '() '()))
(assert-equal '(1) (list-append '() '(1)))
(assert-equal '(a b c d) (list-append '(a b c) '(d)))

(assert-equal '() (list-reverse '()))
(assert-equal '(one two three) (list-reverse '(three two one)))
(assert-equal '(a b c) (list-reverse (list-reverse '(a b c))))
(assert-equal '(a (b) c) (list-reverse '(c (b) a)))

(assert-equal '() (list-flatten '()))
(assert-equal '(a b c) (list-flatten '(a b c)))
(assert-equal '(a b c) (list-flatten '(a (b c))))
(assert-equal '(a b c) (list-flatten '((a) (b (c)))))
(assert-equal '(a b c d) (list-flatten '((a b) (c (d)))))

