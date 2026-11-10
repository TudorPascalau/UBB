% Se da o lista de numere intregi. Se cere sa se scrie de 2 ori in lista
% fiecare numar prim.

prim(N,D):-
	D > N/2,
	!.
prim(N,D):-
	N mod D =\= 0,
	D1 is D+1,
	prim(N,D1).

is_prim(N):-
	N > 1,
	prim(N,2).

prim_lista([],[]).
prim_lista([H|T],[H,H|R]):-
	is_prim(H),
	prim_lista(T,R).
prim_lista([H|T],[H|R]):-
	\+ is_prim(H),
	prim_lista(T,R).
