% Definiti un predicat care, dintr-o lista de atomi, produce o lista de
% perechi (atom n), unde atom apare in lista initiala de n ori. De ex:
% numar([1, 2, 1, 2, 1, 3, 1], X) va produce X = [[1, 4], [2, 2],[3,1]].

% nr_aparitii(E,L,N)
nr_aparitii(_,[],0):-!.
nr_aparitii(H, [H|T], N):-
	!,
	nr_aparitii(H,T,N1),
	N is N1+1.
nr_aparitii(H,[_|T], N):-
	nr_aparitii(H,T,N).

% perechi_atom(L,Viz,R).
perechi_atom([],_,[]).
perechi_atom([H|T],Viz,[P|R]):-
	nr_aparitii(H,Viz,0),
	!,
	nr_aparitii(H,[H|T],N),
	P = [H|N],
	perechi_atom(T,[H|Viz],R).
perechi_atom([_|T],Viz,R):-
	perechi_atom(T,Viz,R).

perechi_start(L,R):-
	perechi_atom(L,[],R).
