;;; -*- Mode: Scheme;  -*-

;; to run
;; ,exec ,load ~/dev/cmu-perq/scheme48/scheme48-1.9.1.git/misc-scripts/build-image.scm


(config)
;(load "scheme/platform-interfaces.scm")
;(load "scheme/rts-packages-64.scm")
;;(load "scheme/low-packages.scm")
(load "~/dev/cmu-perq/scheme48/scheme48-1.9.1.git/misc-scripts/build-image-package.scm")
(load "~/dev/cmu-perq/scheme48/scheme48-1.9.1.git/scheme/debug/tiny-packages.scm")
(user)
(reload-package 'build-image)


(in 'build-image
    (lambda ()
      (run '(load-configuration "scheme/platform-interfaces.scm"))
      (run '(load-configuration "scheme/rts-packages-64.scm"))
      (run '(load-configuration "scheme/interfaces.scm"))
      (run '(load-configuration "scheme/vm/shared-interfaces.scm"))
      (run '(load-configuration "scheme/packages.scm"))
      (run '(flatload initial-structures))
      (run '(load "build/initial.scm"))
      ;; (run '(link-initial-system))
      ))











;; (user)
;; (open 'platform)
;; (open 'cells 'record-types)


;; (open 'debug-data-internal)
;; (load "misc-scripts/exec-script-code-enable-debugging.lisp")


;; (config)
;; ;; interfaces
;; (load "scheme/interfaces.scm")
;; ;; (load "misc-scripts/package-commands-internal-interface-aux.lisp")
;; (load "scheme/platform-interfaces.scm")
;; (load "scheme/more-interfaces.scm")
;; (load "scheme/env-packages.scm")
;; (load "scheme/prescheme/interface.scm")
;; ;; (load "misc-scripts/my-utilities/my-utilities-interfaces.scm")
;; (reload-package 'package-commands-internal)
;; (load "scheme/vm/interfaces.scm")

;; ;; packages

;; ;; (load "scheme/rts-packages.scm")
;; (load "scheme/vm/ps-platform-64-packages.scm")
;; (load "scheme/vm/shared-interfaces.scm")
;; (load "scheme/vm/s48-package-defs.scm")
;; (load "scheme/vm/package-defs.scm")
;; (load "scheme/vm/twospace-gc-package-defs.scm")
;; (load "scheme/vm/debug-package.scm")
;; (load "scheme/prescheme/package-defs.scm")
;; ;;(load "scheme/low-packages.scm")
;; ;; (load "scheme/low-packages.scm")
;; ;;(load "misc-scripts/my-utilities/my-utilities-packages.scm")
;; (reload-package 'destructuring)  ; used in FOR-SYNTAX clause
;; (reload-package 'bigbit)
;; ;; (reload-package 'shared-bindings)
;; ;; (reload-package 'vm)
;; (reload-package 'interpreter)
;; ;; (reload-package 'proposals)








;; ;; someday figure out how to import this.
;; ;; undefine


;; (user)
;; (open 'package-commands-internal)
;; (open 'packages-internal)
;; (open 'packages)
;; (open 'list-interfaces)
;; (open 'table)
;; (open 'util)
;; (open 'command-state)
;; (open 'ps-memory)
;; (open 'vm)
;; (open 'heap-init)
;; (open 'read-image)
;; (open 'memory-debug)
;; (open 'debug-data-internal)
;; (open 'r5rs)
;; (open 'interpreter)
;; (open 'allocation)
;; (open 'heap-gc-util)
;; (open 'heap)
;; (open 'heap-two-space-native-code)
;; (open 'stack)
;; (open 'vmio)
;; (open 'struct)
;; (open 'interpreter-internal) ; files: interp call define-primitive prim
;; (open 'interpreter)          ;        interrupt
;; (open 'external-opcodes)
;; (open 'prescheme)
;; (open 'data)
;; (open 'vm-architecture)
;; (open 'vm-utilities)
;; (open 'disassembler)
;; (open 'architecture)
;; (open 'big-scheme)

;; (exec)
;; (in 'stob '(open big-util)) ;; breakpoint

;; (user)


;; ;;(open 'stob)


;; ;; (load "misc-scripts/exec-script-code.lisp")



;; ;; (start-vm "/home/rett/dev/cmu-perq/scheme48/scheme48-1.9.1.git/build/initial.image-64" 2000000 20000 '#())






;; ;   ,config ,load ../platform-interfaces.scm
;; ; then
;; ;   ,config ,load ps-platform-32-packages.scm
;; ;      - or -
;; ;   ,config ,load ps-platform-64-packages.scm
;; ; (ignoring the warning) and then:
;; ;   ,exec ,load load-vm.scm
