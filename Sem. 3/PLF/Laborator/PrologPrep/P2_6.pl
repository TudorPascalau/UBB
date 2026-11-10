% %Intr-o lista L sa se inlocuiasca toate aparitiile unui element E cu
% elementele unei alte liste, L1.
% De ex: inloc([1,2,1,3,1,4],1,[10,11],X)
% va produce X=[10,11,2,10,11,3,10,11,4].

concat([],L,L).
concat([H|T],L,[H|R]):-
	concat(T,L,R).

inlocuire([],_,_,[]).
inlocuire([H|T],H,L,R):-
	inlocuire(T,H,L,R1),
	concat(L,R1,R).
inlocuire([H|T],E,L,[H|R]):-
	H \= E,
	inlocuire(T,E,L,R).


% Se da o lista eterogena, formata din numere intregi si liste de numere
% intregi. In fiecare sublista sa se inlocuiasca toate aparitiile
% primului element din sublista cu o lista data. De ex: [1, [4, 1, 4],
% 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] si [11, 11]
% => [1, [11, 11, 1, 11, 11], 3, 6, [11, 11, 10, 1, 3, 9], 5, [11 11 11
% 11 11 11], 7]

inlocuire_primul([],_,[]).
inlocuire_primul([H|T],L,[H|R]):-
	\+ is_list(H),
	inlocuire_primul(T,L,R).
inlocuire_primul([H|T],L,[LI|R]):-
	is_list(H),
	H = [HL|_],
	inlocuire(H,HL,L,LI),
	inlocuire_primul(T,L,R).


