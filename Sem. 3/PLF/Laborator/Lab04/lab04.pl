% permutare(N: el, P: list)
% N: numar intreg dat
% P: permutare a numerelor din {1,..,N} ce respecta conditia
% model de flux: (i,o), (i,i)
permutare(N, P):-
    N >= 1,
    construieste(1, N, [], P).

% Cazuri testare
% permutare(4, P).
% permutare(4, [2,1,3,4]).
% permutare(4, [1,3,2,4]).

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

% Cazuri testare
% construieste(2, 2, [1,3], P).
% construieste(2, 3, [1,4], P).
% construieste(2, 2, [1,3], [1,2,3]).
