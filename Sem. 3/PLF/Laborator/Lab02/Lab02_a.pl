
% substitute(L:list, E:el, V:el, R:list)
% model de flux: (i, i, i, o) sau (i, i, i, i)
% L - lista initiala
% E - elementul ale carui aparitii vor fi inlocuite
% V - elementul cu care se inlocuieste E
% R - lista rezultata prin inlocuirea tuturor aparitiilor lui E cu V

substitute([], _, _, []).

substitute([H|T], E, V, [V|R]) :-
    H == E,
    substitute(T, E, V, R).

substitute([H|T], E, V, [H|R]) :-
    H \== E,
    substitute(T, E, V, R).


% Exemple testare
% substitute([], 2, 9, R).
% substitute([1, 2, 3, 2], 2, 9, R).
% substitute([1, 3, 4], 2, 9, R).
% substitute([2, 2, 2], 2, 9, R).
% substitute([1, 2, 2], 2, 2, R).
% substitute([1, 2, 3, 2], 2, 9, [1, 9, 3, 9]).
% substitute([1, 2, 3, 2], 2, 9, [1, 9, 3, 2]).