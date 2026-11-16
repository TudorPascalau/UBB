% Se da o lista de numere intregi. Se cere sa se elimine din lista
% toate secventele (cu cel putin 2 elemente) de elemente de pe pozitii
% consecutive formate din numere prime
% De exemplu [2,3,4,5,6,7,13] => [4,5,6]

prim(N,D):-
	D > N div 2,
	!.
prim(N,D):-
	N mod D =\= 0,
	D =< N div 2,
	D1 is D + 1,
	prim(N,D1).

is_prim(N):-
	N > 1,
	prim(N,2).

% prim_consec(L, R), model de flux (i, o)
prim_consec([], []).
prim_consec([H], [H]).
prim_consec([H1,H2|T], R) :-
    is_prim(H1),
    is_prim(H2),
    !,
    sari_prim(T, Rest),
    prim_consec(Rest, R).
prim_consec([H1,H2|T], [H1|R]) :-
    prim_consec([H2|T], R).

% sari_prim(L, R), model de flux (i, o)
sari_prim([H|T], R) :-
    is_prim(H),
    !,
    sari_prim(T, R).
sari_prim(L, L).
