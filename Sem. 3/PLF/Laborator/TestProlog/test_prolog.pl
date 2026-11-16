% cmmdc(A: int, B: int, R:int)
% Calculeaza cel mai mare divizor comun al doua numere intregi
% A: primul numar intreg dat
% B: al doilea numar intreg dat
% R: cel mai mare divizor comun al lui A si B
% model flux: (i,i,o), (i,i,i).

cmmdc(A,0,A):-
	A > 0,
	!.
cmmdc(A,B,R):-
	B > 0,
	Rest is A mod B,
	cmmdc(B, Rest, R).

% Exemplu test cmmdc(8,12,R).
% -> R = 4.

% cmmmc(A: int, B: int, R: int)
% Calculeaza cel mai mic multiplu comun a doua numere intregi
% A: primul numar intreg dat
% B: al doilea numar intreg dat
% R: cel mai mic multiplu comun al lui A si B
% model de flux (i,i,o), (i,i,i).
cmmmc(0,0,0):-!.
cmmmc(A,B,R):-
	P is A * B,
	cmmdc(A,B,D),
	R is P div D.

% Exemplu test cmmmc(18,12,R).
% -> R = 36.

% cmmmc_list(L: list, R: int)
% Calculeaza cel mai mic multiplu comun a numerelor dintr-o lista de
% numere intregi
% L: lista cu numere intregi data
% R: cel mai mic multiplu comun al numerelor din L
% model de flux: (i,o), (i,i)

cmmmc_list([H],H):-!.
cmmmc_list([H|T],R):-
	cmmmc_list(T,M),
	cmmmc(H,M,R).

% Exemplu test cmmmc_list([2,4,3,5,2],R).
% -> R = 60.
