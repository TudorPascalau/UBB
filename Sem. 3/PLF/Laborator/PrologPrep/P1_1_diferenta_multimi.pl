member(X,[X|_]):-!.
member(X,[_|T]):-
	member(X,T).

diferenta_multimi([],_,[]):-!.
diferenta_multimi([H|T],L,[H|R]):-
	\+ member(H,L),
	!,
	diferenta_multimi(T,L,R).
diferenta_multimi([H|T], L, R) :-
    member(H, L),
    diferenta_multimi(T, L, R).

% adauga_dupa_par(L,R)
adauga_dupa_par([],[]):-!.
adauga_dupa_par([H|T], [H,1|R]):-
	H mod 2 =:= 0,
	!,
	adauga_dupa_par(T,R).
adauga_dupa_par([H|T], [H|R]):-
	adauga_dupa_par(T,R).
