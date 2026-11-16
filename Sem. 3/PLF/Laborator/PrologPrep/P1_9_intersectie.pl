% Sa se scrie un predicat care intoarce intersectia a doua multimi.

member(H,[H|_]).
member(H,[_|T]):-
	member(H,T).

intersect([],_,[]).
intersect([H|T],L,[H|R]):-
	member(H,L),
	intersect(T,L,R).
intersect([H|T],L,R):-
	\+ member(H,L),
	intersect(T,L,R).

% Sa se construiasca lista (m, ..., n), adica multimea numerelor intregi
% din intervalul [m, n].

interval(N,N,[N]):-!.
interval(M,N,[M|R]):-
	M1 is M+1,
	interval(M1,N,R).
