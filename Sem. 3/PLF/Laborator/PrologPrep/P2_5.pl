% Sa se determine pozitiile elementului maxim dintr-o lista liniara.
% De ex: poz([10,14,12,13,14], L) va produce L = [2,5].

maxim([],0).
maxim([H|T],H):-
	maxim(T,R),
	H >= R.
maxim([H|T],R):-
	maxim(T,R),
	H < R.

poz_max([],_,_,[]).
poz_max([H|T],P,M,[P|R]):-
	H = M,
	P1 is P+1,
	poz_max(T,P1,M,R).
poz_max([H|T],P,M,R):-
	H \= M,
	P1 is P+1,
	poz_max(T,P1,M,R).

poz_max_start(L,R):-
	maxim(L,M),
	poz_max(L,1,M,R).
