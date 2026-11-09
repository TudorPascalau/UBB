% permutare_lista(N: el, Lista: list, P: list)
% N: numarul de elemente care trebuie alese din Lista
% Lista: lista de valori intregi distincte din care se aleg elementele
% P: permutarea de lungime N care respecta conditia din enunt
% model de flux: (i,i,o), (i,i,i)
permutare_lista(N, Lista, P) :-
    N >= 1,
    candidat(St, Lista),
    Dr is St + N - 1,
    interval_in_lista(St, Dr, Lista),
    construieste(St, Dr, [], P).

% candidat(E: el, Lista: list)
% E: valoarea generata din Lista sau cautata in Lista
% Lista: lista de valori intregi distincte
% model de flux: (o,i),(i,i)
candidat(E, [E|_]).
candidat(E, [_|R]) :-
    candidat(E, R).


% interval_in_lista(St: intreg, Dr: intreg, Lista: list)
% St: cea mai mica valoare din intervalul verificat
% Dr: cea mai mare valoare din intervalul verificat
% Lista: lista in care se cauta toate valorile de la St la Dr, inclusiv
% model de flux: (i,i,i)
interval_in_lista(X, X, Lista) :-
    candidat(X, Lista).
interval_in_lista(St, Dr, Lista) :-
    St < Dr,
    candidat(St, Lista),
    St1 is St + 1,
    interval_in_lista(St1, Dr, Lista).

% construieste(St: el, Dr: el, Col: list, P: list)
% St: cea mai mica valoare inca nefolosita
% Dr: cea mai mare valoare inca nefolosita
% Col: lista elementelor deja asezate la sfarsitul permutarii
% P: va fi permutarea completa respectand conditia
% model de flux: (i,i,i,o), (i,i,i,i), (i,i,o,i)
construieste(N, N, Col, P):-
	!,
	P = [N|Col].
construieste(St, Dr, Col, P) :-
    St1 is St + 1,
    construieste(St1, Dr, [St|Col], P).

construieste(St, Dr, Col, P) :-
    Dr1 is Dr - 1,
    construieste(St, Dr1, [Dr|Col], P).

