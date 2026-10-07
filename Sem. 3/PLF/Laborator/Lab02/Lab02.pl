
substitute([], _, _, []).
substitute([H|T], E, V, [V|R]) :-
    H = E,
    substitute(T, E, V, R).
substitute([H|T], E, V, [H|R]) :-
    H \= E,
    substitute(T, E, V, R).

