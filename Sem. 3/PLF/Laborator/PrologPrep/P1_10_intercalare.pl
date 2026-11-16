% Sa se intercaleze un element pe pozitia a n-a a unei liste.

intercalare_aux(L,E,N,N,[E|L]).
intercalare_aux([H|T],E,I,N,[H|R]):-
	I < N,
	I1 is I+1,
	intercalare_aux(T,E,I1,N,R).

intercalare(L,E,N,R):-
	intercalare_aux(L,E,1,N,R).

% Definiti un predicat care intoarce cel mai mare divizor comun al
% numerelor dintr-o lista.

cmmdc(A,0,A).
cmmdc(A,B,R):-
	B > 0,
	Rest is A mod B,
	cmmdc(B,Rest,R).
