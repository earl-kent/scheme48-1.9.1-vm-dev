



(define (link-system-work)
  (load-configuration "scheme/platform-interfaces.scm")
  (load-configuration "scheme/rts-packages-64.scm")
  (load-configuration "scheme/interfaces.scm")
  (load-configuration "scheme/vm/shared-interfaces.scm")
  (load-configuration "scheme/packages.scm")
  (flatload initial-structures)
  (load "build/initial.scm")
  (link-initial-system))




;; (define (link-system structs make-resumer filename)

;;   (with-fresh-compiler-state
;;    (if *debug-linker?* 100000 0)    ;Location uid
;;    (lambda ()
;;      (breakpoint "Made it: link-system")
;;      (set! *loser* #f)
;;      (let* ((location-info (make-table))
;; 	    (generator (make-location-generator location-info
;; 						(if *debug-linker?* 10000 0)))
;; 	    (templates (compile-structures structs
;; 					   generator
;; 					   package->environment))
;; 	    (package (make-simple-package structs #f #f))
;; 	    (startup-template (begin
;; 				(set-package-get-location! package generator)
;; 				(expand&compile-form (make-resumer) package))))
;;        (let ((startup (make-closure
;; 		       (make-startup-procedure templates startup-template)
;; 		       0)))
;; 	 (if *debug-linker?* (set! *loser* startup))
;; 	 (write-image-file startup
;; 			   (namestring filename #f 'image)))
;;        (write-debug-info location-info
;; 			 (namestring filename #f 'debug))))))
