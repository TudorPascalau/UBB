% Definiti un predicat care determina succesorul unui numar reprezentat
% cifra cu cifra intr-o lista. De ex: [1 9 3 5 9 9] => [1 9 3 6 0 0]

invers(L,R):-
	invers_aux(L,[],R).

invers_aux([],Col,Col).
invers_aux([H|T],Col,R):-
	invers_aux(T,[H|Col],R).

suma(L,C,R):-
	invers(L,LI),
	suma_aux(LI,C,0,RI),
	invers(RI,R).

suma_aux([],_,0,[]):-!.
suma_aux([],_,Tr,[Tr]):-
	Tr > 0.
suma_aux([H|T],C,Tr,[Cif|R]):-
	P is H + C + Tr,
	Cif is P mod 10,
	Trans is P div 10,
	inmultire_aux(T,C,Trans,R).

succesor(L,R):-
	suma(L,1,R).

