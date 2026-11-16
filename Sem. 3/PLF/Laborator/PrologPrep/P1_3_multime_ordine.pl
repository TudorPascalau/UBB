% Sa se scrie un predicat care transforma o lista intr-o multime, in
% ordinea primei aparitii. Exemplu: [1,2,3,1,2] e transformat in
% [1,2,3].

member(X,[X|_]):-!.
member(X,[_|T]):-
	member(X,T).

multime_lista(L, R):-
	multime_lista_aux(L, [], R).

multime_lista_aux([], _, []).
multime_lista_aux([H|T], Vazute, R):-
	member(H, Vazute),
	!,
	multime_lista_aux(T, Vazute, R).
multime_lista_aux([H|T], Vazute, [H|R]):-
	multime_lista_aux(T, [H|Vazute], R).

% lista pare / impare
lista_para_impara([],[],[],0,0):-!.
lista_para_impara([H|T],[H|R],LI,P,I):-
	H mod 2 =:= 0,
	!,
	lista_para_impara(T,R,LI,P1,I),
	P is P1+1.
lista_para_impara([H|T],LP,[H|R],P,I):-
	lista_para_impara(T,LP,R,P,I1),
	I is I1+1.

lista(L,R,P,I):-
	lista_para_impara(L,LP,LI,P,I),
	R=[LP,LI].
