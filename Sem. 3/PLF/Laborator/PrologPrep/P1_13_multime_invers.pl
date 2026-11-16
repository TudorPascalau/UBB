% Sa se scrie un predicat care transforma o lista intr-o multime, in
% ordinea ultimei aparitii. Exemplu: [1,2,3,1,2] e transformat in
% [3,1,2].

member(X,[X|_]):-!.
member(X,[_|T]):-
	member(X,T).

multime_lista([], []):-!.
multime_lista([H|T], [H|R]):-
	\+ member(H,T),
	!,
	multime_lista(T,R).
multime_lista([_|T],R):-
	multime_lista(T,R).

