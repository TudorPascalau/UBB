% Dandu-se o lista liniara numerica, sa se stearga toate secventele de
% valori consecutive.
% Ex: sterg([1, 2, 4, 6, 7, 8, 10], L) va produce L=[4, 10].

% sterge_consecutiv(L, R), flux (i, o)
% L este lista initiala, R este lista fara secventele consecutive.
sterge_consecutiv([], []).
sterge_consecutiv([H], [H]).
sterge_consecutiv([H1,H2|T], R) :-
    H2 =:= H1 + 1,
    sari_consecutive(H2, T, Rest),
    sterge_consecutiv(Rest, R).
sterge_consecutiv([H1,H2|T], [H1|R]) :-
    H2 =\= H1 + 1,
    sterge_consecutiv([H2|T], R).

% sari_consecutive(Ultim, L, Rest), flux (i, i, o)
% Ultim este ultima valoare eliminata, L este coada de verificat,
% iar Rest incepe la primul element din afara secventei.
sari_consecutive(_, [], []).
sari_consecutive(Ultim, [H|T], Rest) :-
    H =:= Ultim + 1,
    sari_consecutive(H, T, Rest).
sari_consecutive(Ultim, [H|T], [H|T]) :-
    H =\= Ultim + 1.

% Se da o lista eterogena, formata din numere intregi si liste de numere
% intregi. Din fiecare sublista sa se stearga toate secventele de valori
% consecutive. De ex: [1, [2, 3, 5], 9, [1, 2, 4, 3, 4, 5, 7, 9], 11,
% [5, 8, 2], 7] => [1, [5], 9, [4, 7, 9], 11, [5, 8, 2], 7]

elimina_consecutive([],[]).
elimina_consecutive([H|T],[H|R]):-
	\+ is_list(H),
	elimina_consecutive(T,R).
elimina_consecutive([H|T],[LR|R]):-
	is_list(H),
	sterge_consecutiv(H,LR),
	elimina_consecutive(T,R).

