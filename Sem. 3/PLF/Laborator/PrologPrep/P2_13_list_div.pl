% Sa se adauge dupa fiecare element dintr-o lista divizorii elementului.

concat([],L,L).
concat([H|T],L,[H|R]):-
	concat(T,L,R).

list_div(N,N,[N]):-!.
list_div(N,D,[D|R]):-
	N mod D =:= 0,
	D1 is D + 1,
	list_div(N,D1,R).
list_div(N,D,R):-
	N mod D =\= 0,
	D1 is D + 1,
	list_div(N,D1,R).

list_div_add([],[]).
list_div_add([H|T],[H|Rez]):-
	list_div(H,1,D),
	list_div_add(T,R),
	concat(D,R,Rez).
