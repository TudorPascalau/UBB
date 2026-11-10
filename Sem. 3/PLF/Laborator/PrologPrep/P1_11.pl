% Sa se scrie un predicat care sa testeze daca o lista formata din numere
% intregi are aspect de "vale"(o multime se spune ca are aspect de "vale"
% daca elementele descresc pana la un moment dat, apoi cresc.
% De ex. 10 8 6 9 11 13).

vale([_],1):-!.
vale([H1,H2|T], 0):-
	H1 > H2,
	!,
	vale([H2|T],0).
vale([H1,H2|T],_):-
	H1 < H2,
	!,
	vale([H2|T],1).

vale_start([H1,H2|T]):-
	H1 > H2,
	vale([H1,H2|T], 0).


% Sa se calculeze suma alternanta a elementelor unei liste
% (l1 - l2 + l3 ...).

suma_alt([],_,0).
suma_alt([H|T],0,R):-
	suma_alt(T,1,R1),
	R is H+R1.
suma_alt([H|T],1,R):-
	suma_alt(T,0,R1),
	R is R1-H.
suma_alt_start(L,R):-
	suma_alt(L,0,R).












