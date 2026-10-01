male(harry).
female(liz).
parent(phil, chas).
parent(liz, chas).
parent(liz, mary).

parent(chas, harry).
parent(chas, willis).
parent(chas, anabelle).

grandmother(GM, C):-
    mother(GM, P),
    parent(P, C).

mother(M, C):-
    female(M),
    parent(M, C).

siblings(F1, F2):-
    parent(P, F1),
    parent(P, F2).

siblings(F1, F2, F3):-
    parent(P, F1),
    parent(P, F2),
    parent(P, F3).