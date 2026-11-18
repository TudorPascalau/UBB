;; Functie care verifica daca o lista este liniara
;; lista-liniara(l: list) -> t/nil
;; l: lista de verificat
(defun lista-liniara (l)
	(cond
		((null l) t)
		((atom (car l)) (lista-liniara (cdr l)))
		(t nil)
	)
)
;; Exemple testare
;(lista-liniara-p '())
;(lista-liniara-p '(a 2 c))
;(lista-liniara-p '(a (b c) d))
;(lista-liniara-p '(a () b))

;; Functie care substituie prima aparitie a unui element intr-o lista data
;; subst-prim(l: list, vechi: el, nou: el) -> list
;; l: lista in care inlocuim
;; vechi: elementul de inlocuit
;; nou: elementul cu care inlocuim
(defun subst-prim (l vechi nou)
	(cond
		((null l) nil)
		((equal (car l) vechi) (cons nou (cdr l)))
		(t (cons (car l) (subst-prim (cdr l) vechi nou)))
	)
)

;; Exemple testare
;(substituie-prima '(a b a c) 'a 'x)
;(substituie-prima '(a b b c) 'b 'x)
;(substituie-prima '(a b c) 'z 'x)
;(substituie-prima '() 'a 'x)
;(substituie-prima '((a b) c) '(a b) 'x)

;; Urmareste ultimul element al listei pana ajunge la un atom.
;; ultimul-atom(l: list) -> atom
;; l: lista din care se extrage ultimul element
(defun ultimul-atom (l)
	(cond
		((null l) nil)
		((cdr l) (ultimul-atom (cdr l)))
		((listp (car l)) (ultimul-atom (car l)))
		(t (car l))
	)
)

;; Inlocuieste fiecare sublista de la primul nivel cu atomul obtinut
;; urmarind ultimul element al sublistei.
;; inlocuieste-subliste(l: list) -> list
;; l: lista de prelucrat
(defun inlocuieste-subliste (l)
  (cond
    ((null l) nil)
    ((listp (car l))(cons (ultimul-atom (car l))
						  (inlocuieste-subliste (cdr l))))
    (t (cons (car l)
			 (inlocuieste-subliste (cdr l))))))

;; Exemple de testare
; (inlocuieste-subliste '(a (b c) (d (e (f)))))
; (inlocuieste-subliste '(a (b c) (d ((e) f))))
; (inlocuieste-subliste '(a b c))
; (inlocuieste-subliste '(a () b))
; (inlocuieste-subliste '())

;; Interclaseaza doua liste sortate crescator, fara dubluri.
;; interclasare-fara-dubluri(l1: list, l2: list) -> list
;; l1, l2: liste liniare de numere, sortate crescator, fiecare fara dubluri
(defun interclasare-fara-dubluri (l1 l2)
	(cond
		((null l1) l2)
		((null l2) l1)
		((< (car l1) (car l2))
			(cons (car l1) (interclasare-fara-dubluri (cdr l1) l2)))
		((> (car l1) (car l2))
			(cons (car l2) (interclasare-fara-dubluri l1 (cdr l2))))
		(t (cons (car l1) (interclasare-fara-dubluri (cdr l1) (cdr l2))))
	)
)

;; Exemple de testare
; (interclasare-fara-dubluri '(1 3 5) '(2 3 4))
; (interclasare-fara-dubluri '(1 3) '(1 3))
; (interclasare-fara-dubluri '() '(2 4))
; (interclasare-fara-dubluri '(1 3) '())