(set-logic QF_NRA)
(declare-fun x () Bool)
(declare-fun y () Bool)
(assert (= x true))
(assert (= y true))
(assert (or
         (not x)
         (not y)))
(check-sat)
(exit)