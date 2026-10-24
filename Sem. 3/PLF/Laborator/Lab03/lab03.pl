% prefixPar(L:list, R:list)
% L: lista data
% R: cel mai lung prefix de numere pare din L
% model flux: (i,o), (i,i)
prefixPar([],[]).
prefixPar([H|_], []):-
	H mod 2 =\= 0.

prefixPar([H|T],[H|R]):-
	H mod 2 =:= 0,
	prefixPar(T,R).

% lungime(L:list, R:number)
% L: lista data
% R: lungimea listei L
% model flux: (i,o), (i,i)
lungime([], 0).
lungime([_|T], R):-
	lungime(T, R1),
	R is R1+1.

% alegeMax(L1:list, L2:list, R:list)
% L1: prima lista data
% L2: a doua lista data
% R: lista cu lungime mai mare dintre L1 si L2
% model flux: (i,i,o), (i,i,i)
alegeMax(L1,L2,L1):-
	lungime(L1,N),
	lungime(L2,M),
	N >= M.

alegeMax(L1,L2,L2):-
	lungime(L1,N),
	lungime(L2,M),
	N < M.

% secventaMaxPara(L:list, R:list)
% L: lista data
% R: secventa de numere pare de lungime maxima din L
% model flux: (i,o), (i,i)
secventaMaxPara([],[]).
secventaMaxPara([H|T],R):-
	prefixPar([H|T], P),
	secventaMaxPara(T, S),
	alegeMax(P,S,R).

% inlocuireSublisteSecventaMaxPara(L:list, R:list)
% L: lista initiala
% R: lista obtinuta prin inlocuire sublistelor din L cu liste
%    reprezentand secventa de numere pare de lungime maxima
% model flux: (i,o), (i,i)
inlocuireSublisteSecventaMaxPara([],[]).
inlocuireSublisteSecventaMaxPara([H|T],[H|R]):-
	number(H),
	inlocuireSublisteSecventaMaxPara(T,R).

inlocuireSublisteSecventaMaxPara([H|T],[S|R]):-
	is_list(H),
	secventaMaxPara(H,S),
	inlocuireSublisteSecventaMaxPara(T,R).

% test cases a)
% secventaMaxPara([], R).
% secventaMaxPara([1, 3, 5], R).
% secventaMaxPara([2, 4, 6], R).
% secventaMaxPara([1, 2, 4, 6, 3, 8], R).
% secventaMaxPara([2, 1, 4, 6, 8], R).
% secventaMaxPara([2, 4, 1, 6, 8], R).
% secventaMaxPara([-4, -2, 0, 3, 6], R).
% secventaMaxPara([8, 2, 10, 3], R).
% secventaMaxPara([1, 2, 4, 3], [2, 4]).
% secventaMaxPara([1, 2, 4, 3], [2]).

% test cases b)
% inlocuireSublisteSecventaMaxPara([], R).
% inlocuireSublisteSecventaMaxPara([1, 2, 3], R).
% inlocuireSublisteSecventaMaxPara([1, [], [1, 3, 5], 2], R).
% inlocuireSublisteSecventaMaxPara([[2, 4], 3, [6, 8]], R).
% inlocuireSublisteSecventaMaxPara([[2, 4, 1, 6, 8], [-4, 0, 3], 7], R).
% inlocuireSublisteSecventaMaxPara([1, [2, 1, 4, 6, 7], 5, [1, 2, 3, 4],
				    % 2, [1, 4, 6, 8, 3], 2, [1, 5], 3], R).
% inlocuireSublisteSecventaMaxPara([1, [2, 4, 3]], [1, [2, 4]]).
% inlocuireSublisteSecventaMaxPara([1, [2, 4, 3]], [1, [2]]).
