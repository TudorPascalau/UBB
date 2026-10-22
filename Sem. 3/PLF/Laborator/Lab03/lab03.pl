prefixPar([],[]).
prefixPar([H|_], []):-
	H mod 2 =\= 0.
prefixPar([H|T],[H|R]):-
	H mod 2 =:= 0,
	prefixPar(T,R).

lungime([], 0).
lungime([_|T], R):-
	lungime(T, R1),
	R is R1+1.

alegeMax(L,P,L):-
	lungime(L,N),
	lungime(P,M),
	N >= M.

alegeMax(L,P,P):-
	lungime(L,N),
	lungime(P,M),
	N < M.

secventaMaxPara([],[]).
secventaMaxPara([H|T],R):-
	prefixPar([H|T], P),
	secventaMaxPara(T, S),
	alegeMax(P,S,R).

inlocuireSublisteSecventaMaxPara([],[]).
inlocuireSublisteSecventaMaxPara([H|T],[H|R]):-
	number(H),
	inlocuireSublisteSecventaMaxPara(T,R).
inlocuireSublisteSecventaMaxPara([H|T],[S|R]):-
	is_list(H),
	secventaMaxPara(H,S),
	inlocuireSublisteSecventaMaxPara(T,R).
