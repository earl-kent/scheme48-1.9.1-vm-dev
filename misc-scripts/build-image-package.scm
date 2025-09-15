
;; (translate "=scheme48/" "./")

(define-structure build-image (export car)
  (open (subset signals (warn))
	features
	code-quote
	bitwise
	ascii
	code-vectors
	number-i/o
	wind
	(subset  i/o (write-byte))
	(subset ports (set-port-crlf?!))
	platform
	cells record-types
	scheme-level-1
	scheme
	exceptions
	tiny-system
	(subset big-util (breakpoint)))
  (files "../scheme/rts/util.scm"
	 "../scheme/rts/defenum.scm"
	 "../scheme/vm/interp/arch.scm"
	 "../scheme/alt/jar-defrecord.scm"
	 "../scheme/big/general-table.scm"
	 "../scheme/bcomp/mtype.scm"
	 "../scheme/alt/locations.scm"
	 "../scheme/bcomp/binding.scm"
	 "../scheme/alt/../rts/low-syntax.scm"
	 "../scheme/bcomp/cenv.scm"
	 "../scheme/bcomp/name.scm"
	 "../scheme/bcomp/transform.scm"
	 "../scheme/alt/fluid.scm"
	 "../scheme/alt/weak.scm"
	 "../scheme/rts/population.scm"
	 "../scheme/bcomp/interface.scm"
	 "../scheme/alt/template.scm"
	 "../scheme/rts/template.scm"
	 "../scheme/bcomp/thingie.scm"
	 "../scheme/bcomp/package.scm"
	 "../scheme/bcomp/package-undef.scm"
	 "../scheme/bcomp/node.scm"
	 "../scheme/bcomp/schemify.scm"
	 "../scheme/bcomp/var-util.scm"
	 "../scheme/bcomp/primop.scm"
	 "../scheme/bcomp/ddata.scm"
	 "../scheme/bcomp/state.scm"
	 "../scheme/bcomp/frame.scm"
	 "../scheme/bcomp/segment.scm"
	 "../scheme/bcomp/optimize.scm"
	 "../scheme/bcomp/flatten.scm"
	 "../scheme/bcomp/recon.scm"
	 "../scheme/bcomp/comp-exp.scm"
	 "../scheme/bcomp/comp-lambda.scm"
	 "../scheme/bcomp/comp-prim.scm"
	 "../scheme/bcomp/comp.scm"
	 "../scheme/alt/closure.scm"
	 "../scheme/link/data.scm"
	 "../scheme/link/transport.scm"
	 "../scheme/link/write-image.scm"
	 "../scheme/bcomp/syntax.scm"
	 "../scheme/env/debuginfo.scm"
	 "../scheme/big/filename.scm"
	 "../scheme/bcomp/read-form.scm"
	 "../scheme/bcomp/scan-package.scm"
	 "../scheme/rts/syntax-rules-data.scm"
	 "../scheme/bcomp/syntax-rules-compiler.scm"
	 "../scheme/bcomp/usual.scm"
	 "../scheme/bcomp/syntax-rules.scm"
	 "../scheme/bcomp/comp-package.scm"
	 "../scheme/big/strong.scm"
	 "../scheme/opt/usage.scm"
	 "../scheme/opt/sort.scm"
	 "../scheme/opt/inline.scm"
	 "../scheme/link/reify.scm"
	 "../scheme/rts/syntax-rules-apply.scm"
	 "../scheme/alt/loophole.scm"
	 "../scheme/bcomp/type.scm"
	 "../scheme/alt/low.scm"
	 "../scheme/bcomp/module-language.scm"
	 "../scheme/bcomp/config.scm"
	 "../scheme/opt/analyze.scm"
	 "../scheme/alt/environments.scm"
	 "../scheme/link/loadc.scm"
	 "../scheme/env/flatload.scm"
	 "../scheme/alt/init-defpackage.scm"
	 "../scheme/link/link.scm"
	 ;; "../build/initial.scm"
	 ;; "build-image-utils.scm"
	 ))
