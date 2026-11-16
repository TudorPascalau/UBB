invers_aux([],Col,Col).
invers_aux([H|T],Col,R):-
	invers_aux(T,[H|Col],R).

invers(L,R):-
	invers_aux(L,[],R).

suma(L1,L2,R):-
	invers(L1,LR1),
	invers(L2,LR2),
	suma_aux(LR1,LR2,0,RR),
	invers(RR,R).

suma_aux([],[],0,[]):-!.
suma_aux([],[],T,[T]):-
	T > 0,
	!.

suma_aux([H|T],[],Tr,[Cif|R]):-
	S is H + Tr,
	Cif is S mod 10,
	Trans is S div 10,
	suma_aux(T,[],Trans,R).

suma_aux([],[H|T],Tr,[Cif|R]):-
	S is H + Tr,
	Cif is S mod 10,
	Trans is S div 10,
	suma_aux([],T,Trans,R).

suma_aux([H1|T1],[H2|T2],Tr,[Cif|R]):-
	S is H1 + H2 + Tr,
	Cif is S mod 10,
	Trans is S div 10,
	suma_aux(T1,T2,Trans,R).

