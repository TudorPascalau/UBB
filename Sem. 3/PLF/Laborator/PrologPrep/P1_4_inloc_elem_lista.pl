% Sa se scrie un predicat care substituie intr-o lista un element printr-o
% alta lista.

% subst(Lista, E, L, R) - (i, i, i, o)
% Inlocuieste fiecare aparitie a lui E cu elementele listei L.
subst([], _, _, []).

subst([H|T], E, L, [H|R]) :-
    H \= E,
    subst(T, E, L, R).

subst([E|T], E, L, R) :-
    subst(T, E, L, RT),
    concateneaza(L, RT, R).

% concateneaza(A, B, R) - (i, i, o)
% R contine elementele lui A urmate de elementele lui B.
concateneaza([], B, B).
concateneaza([H|T], B, [H|R]) :-
    concateneaza(T, B, R).

% Sa se elimine elementul de pe pozitia a n-a a unei liste liniare.

elim([],_,_,[]).
elim([H|T],I,K,[H|R]):-
	I \= K,
	I1 is I+1,
	elim(T,I1,K,R).
elim([_|T],I,K,R):-
	I = K,
	I1 is I+1,
	elim(T,I1,K,R).

elim_start(L,K,R):-
	elim(L,1,K,R).
