% Se da o lista de numere intregi. Se cere sa se adauge in lista dupa 1-ul
% element, al 3-lea element, al 7-lea elemen, al 15-lea element …
% o valoare data e.

insert_aux([],_,_,_,[]).
insert_aux([H|T],E,I,K,[H|R]):-
	I \= K,
	I1 is I+1,
	insert_aux(T,E,I1,K,R).
insert_aux([H|T],E,I,K,[H,E|R]):-
	I = K,
	I1 is I+1,
	K1 is K*2+1,
	insert_aux(T,E,I1,K1,R).

insert(L,E,R):-
	insert_aux(L,E,1,1,R).

% %Se da o lista eterogena, formata din numere intregi si liste de numere
% intregi. Lista incepe cu un numar si nu sunt 2 elemente consecutive
% care sunt liste. Se cere ca in fiecare sublista sa se adauge dupa 1-ul,
% al 3 lea, al 7-lea… element valoarea care se gaseste inainte de
% sublista in lista eterogena.
% De ex: [1, [2, 3], 7, [4, 1, 4], 3, 6, [7, 5, 1, 3, 9, 8, 2, 7], 5]
% => [1, [2, 1, 3], 7, [4, 7, 1, 4, 7], 3, 6, [7, 6, 5, 1, 6, 3, 9, 8,
% 2, 6, 7], 5].

insert_lista([],[]).
insert_lista([H1,H2|T],[H1,LR|R]):-
	is_list(H2),
	insert(H2,H1,LR),
	insert_lista(T,R).
insert_lista([H|T],[H|R]):-
	\+ is_list(H),
	insert_lista(T,R).
