% Sa se sorteze o lista cu pastrarea dublurilor.

% sortare(L, R) - (i, o)
% L - lista de numere, R - lista sortata cu dubluri
sortare([], []).
sortare([H|T], R) :-
    sortare(T, TS),
    insereaza(H, TS, R).

% insereaza(X, L, R) - (i, i, o)
% X - numarul de inserat, L - lista deja sortata, R - rezultatul
insereaza(X, [], [X]).
insereaza(X, [H|T], [X,H|T]) :-
    X =< H.
insereaza(X, [H|T], [H|R]) :-
    X > H,
    insereaza(X, T, R).
