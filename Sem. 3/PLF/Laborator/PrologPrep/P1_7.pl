% Sa se scrie un predicat care, primind o lista, intoarce multimea
% tuturor perechilor din lista. De ex, cu [a, b, c, d] va produce
% [[a, b], [a, c], [a, d], [b, c], [b, d],

candidat(H,[H|_]).
candidat(H,[_|T]):-
	candidat(H,T).

% perechi(L,R,K)
pereche([A|T], [A,B]) :-
    candidat(B, T).
pereche([_|T], P) :-
    pereche(T, P).

perechi_start(L, R) :-
    findall(P, pereche(L, P), R).
