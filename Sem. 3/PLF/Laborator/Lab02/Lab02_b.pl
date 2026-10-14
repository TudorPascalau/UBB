% sublist(L:list, M:integer, N:integer, R:list)
% model de flux: (i, i, i, o) sau (i, i, i, i)
% L - lista initiala
% M - pozitia de inceput a sublistei, numerotata de la 1
% N - pozitia de sfarsit a sublistei, inclusa in rezultat
% R - sublista formata din elementele lui L de pe pozitiile M,...,N

sublist(_, _, 0, []).

sublist([], _, N, []) :-
    N > 0.

sublist([H|T], 1, N, [H|R]) :-
    N > 0,
    N1 is N - 1,
    sublist(T, 1, N1, R).

sublist([_|T], M, N, R) :-
    M > 1,
    N > 0,
    M1 is M - 1,
    N1 is N - 1,
    sublist(T, M1, N1, R).


% Exemple testare
% sublist([10,20,30,40,50], 2, 4, R).
% sublist([10,20,30,40,50], 1, 3, R).
% sublist([10,20,30,40,50], 3, 5, R).
% sublist([10,20,30], 1, 3, R).
% sublist([10,20,30], 1, 1, R).
% sublist([10,20,30], 3, 3, R).
% sublist([10], 1, 1, R).
% sublist([2,2,3,2,4], 2, 4, R).[2,3,2].
% sublist([10,20,30,40], 2, 3, [20,30]).
% sublist([10,20,30,40], 2, 3, [10,20]).
% sublist([40,50], 1, 0, R).


