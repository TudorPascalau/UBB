%Sa se scrie un predicat care testeaza daca o lista este multime.

member(H,[H|_]).
member(H,[_|T]):-
	member(H,T).

multime([]).
multime([H|T]):-
	\+ member(H,T),
	multime(T).

% Sa se scrie un predicat care elimina primele 3 aparitii ale unui
% element intr-o lista. Daca elementul apare mai putin de 3 ori, se va
% elimina de cate ori apare.

elim3([],_,_,[]).
elim3([H|T],H,K,R):-
	K =< 3,
	!,
	K1 is K+1,
	elim3(T,H,K1,R).
elim3([H|T],E,K,[H|R]):-
	elim3(T,E,K,R).

elim3_start(L,E,R):-
	elim3(L,E,1,R).
