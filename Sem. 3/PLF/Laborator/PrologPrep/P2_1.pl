% Definiti un predicat care determina suma a doua numere scrise in
% reprezentare de lista.

% suma_numere(A, B, R) - (i, i, o)
% A, B - listele de cifre ale celor doua numere
% R - lista de cifre a sumei
suma_numere(A, B, R) :-
    invers_aux(A, [], AI),
    invers_aux(B, [], BI),
    suma_aux(AI, BI, 0, [], R).

% invers_aux(L, Col, R) - (i, i, o)
% L - lista ramasa, Col - cifrele colectate, R - rezultatul
invers_aux([], Col, Col).
invers_aux([H|T], Col, R) :-
    invers_aux(T, [H|Col], R).

% suma_aux(A, B, T, Col, R) - (i, i, i, i, o)
% A, B - cifrele ramase, de la cea mai putin semnificativa
% T - transportul, Col - cifrele calculate, R - suma finala
suma_aux([], [], 0, Col, Col).
suma_aux([], [], 1, Col, [1|Col]).

suma_aux([A|As], [B|Bs], T, Col, R) :-
    S is A + B + T,
    Cifra is S mod 10,
    Transport is S div 10,
    suma_aux(As, Bs, Transport, [Cifra|Col], R).

suma_aux([], [B|Bs], T, Col, R) :-
    suma_aux([0], [B|Bs], T, Col, R).

suma_aux([A|As], [], T, Col, R) :-
    suma_aux([A|As], [0], T, Col, R).

% Se da o lista eterogena, formata din numere intregi si liste de cifre.
% Sa se calculeze suma tuturor numerelor reprezentate de subliste.

% suma_subliste(L, R) - (i, o)
% L - lista eterogena de intregi si liste de cifre
% R - suma numerelor reprezentate de subliste, ca lista de cifre
suma_subliste(L, R) :-
    suma_subliste_aux(L, [0], R).

% suma_subliste_aux(L, Col, R) - (i, i, o)
% L - lista ramasa, Col - suma acumulata, R - suma finala
suma_subliste_aux([], Col, Col).

suma_subliste_aux([H|T], Col, R) :-
    integer(H),
    suma_subliste_aux(T, Col, R).

suma_subliste_aux([H|T], Col, R) :-
    is_list(H),
    suma_numere(Col, H, ColNou),
    suma_subliste_aux(T, ColNou, R).

