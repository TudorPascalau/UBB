% Definiti un predicat care determina produsul unui numar reprezentat
% cifra cu cifra intr-o lista cu o anumita cifra.
% De ex: [1 9 3 5 9 9] * 2 => [3 8 7 1 9 8]

invers(L,R):-
	invers_aux(L,[],R).

invers_aux([],Col,Col).
invers_aux([H|T],Col,R):-
	invers_aux(T,[H|Col],R).

inmultire(L,C,R):-
	invers(L,LI),
	inmultire_aux(LI,C,0,RI),
	invers(RI,R).

inmultire_aux([],_,0,[]):-!.
inmultire_aux([],_,Tr,[Tr]):-
	Tr > 0.
inmultire_aux([H|T],C,Tr,[Cif|R]):-
	P is H * C + Tr,
	Cif is P mod 10,
	Trans is P div 10,
	inmultire_aux(T,C,Trans,R).

% Se da o lista eterogena, formata din numere intregi si maximum 9 liste de
% numere intregi. Sa se inlocuiasca fiecare sublista cu rezultatul
% inmultirii sublistei cu numarul de ordine al sublistei (prima sublista
% cu 1, a 2-a cu 2, etc.). De ex: [1, [2, 3], [4, 1, 4], 3, 6, [7, 5, 1,
% 3, 9], 5, [1, 1, 1], 7] => [1, [2, 3], [8, 2, 8], 3, 6, [2, 2, 5, 4, 1,
% 7], 5, [4, 4, 4], 7]

inmultire_ordine([],_,[]).
inmultire_ordine([H|T],K,[H|R]):-
	\+ is_list(H),
	inmultire_ordine(T,K,R).
inmultire_ordine([H|T],K,[P|R]):-
	is_list(H),
	inmultire(H,K,P),
	K1 is K+1,
	inmultire_ordine(T,K1,R).

inmultire_start(L,R):-
	inmultire_ordine(L,1,R).
