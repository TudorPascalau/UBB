% Sa se interclaseze fara pastrarea dublurilor doua liste sortate.

interclasare([],[],[]).
interclasare([H|T],[],[H|R]):-
	interclasare(T,[],R).
interclasare([],[H|T],[H|R]):-
	interclasare([],T,R).
interclasare([H1|T1],[H2|T2],[H1|R]):-
	H1 < H2,
	interclasare(T1,[H2|T2],R).
interclasare([H1|T1],[H2|T2],[H1|R]):-
	H1 = H2,
	interclasare(T1,T2,R).
interclasare([H1|T1],[H2|T2],[H2|R]):-
	H2 < H1,
	interclasare([H1|T1],T2,R).
