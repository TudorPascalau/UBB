% Sa se scrie un predicat care determina cel mai mic multiplu comun al
% elementelor unei liste formate din numere intreg

cmmdc(A,0,A):-
	A > 0,
	!.
cmmdc(A,B,R):-
	B > 0,
	Rest is A mod B,
	cmmdc(B, Rest, R).

cmMmc(A,B,R):-
	cmmdc(A,B,C),
	R is A*B/C.

multiplu_lista([H], H):-!.
multiplu_lista([H|T], Rez):-
	multiplu_lista(T,R),
	cmMmc(H,R,Rez).

% Sa se scrie un predicat care adauga dupa 1-ul, al 2-lea, al 4-lea, al
% 8-lea ...element al unei liste o valoare v data.

% inserare(L, V, I, K, R)
inserare([],_,_,_,[]):-!.
inserare([H|T],V,K,K,[H,V|R]):-
	!,
	K1 is K+1,
	K2 is K*2,
	inserare(T,V,K1,K2,R).
inserare([H|T],V,I,K,[H|R]):-
	I1 is I+1,
	inserare(T,V,I1,K,R).

inserare_start(L,V,R):-
	inserare(L,V,1,1,R).
