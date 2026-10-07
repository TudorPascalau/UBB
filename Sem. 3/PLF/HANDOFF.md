# PLF — predare între proiectele locale

Ultima actualizare: 7 octombrie 2026  
Folder PLF: `E:\Facultate\UBB\Sem. 3\PLF`  
Proiect local de referință: MAP, `E:\Facultate\UBB\Sem. 3\MAP`  
Context MAP: `E:\Facultate\UBB\Sem. 3\MAP\HANDOFF.md`

## Scop și utilizare

Acest fișier păstrează contextul PLF pentru continuarea discuției din acest proiect sau din alte proiecte locale. La începutul unei sesiuni, citește documentul și verifică fișierele relevante. La final, actualizează secțiunea „Ultima sesiune” cu lucrul realizat efectiv, verificările și următorul pas.

Din alt proiect, consultă originalul de la `E:\Facultate\UBB\Sem. 3\PLF\HANDOFF.md`. Dacă folosești o copie, precizează data și proiectul sursă și reconciliază modificările cu originalul când ai acces. Documentul transmite context; nu sincronizează automat fișierele și nu trimite mesaje între chaturi. Accesul la scriere în alt proiect depinde de permisiunile sesiunii.

## Materiale didactice — context din README

Fișierele C++ și Python din `Laborator/Lab01/R1/ListaRecursiva/` și `Laborator/Lab01/R1/ModelImplementare/`, precum și materialele din `Demo/`, sunt exemple pentru ilustrarea logicii, recursivității și conceptelor prezentate la curs sau laborator. Nu este obligatoriu să compileze ori să ruleze integral în forma păstrată în proiect.

Aceste materiale pot conține fragmente incomplete, erori de sintaxă, denumiri inconsistente sau comportamente neacoperite. În contextul lor didactic, asemenea erori nu sunt defecte de remediat automat.

- Nu raporta erorile acestor exemple ca probleme ale soluțiilor proprii de laborator.
- Nu modifica automat exemplele și nu unifica variantele C++ și Python; ele pot ilustra separat același concept.
- Când explici un exemplu, precizează limitele care influențează explicația, fără să presupui că trebuie reparat.
- Verifică separat soluțiile proprii de laborator: nota nu le scutește de corectitudine și execuție.

Nota se aplică exclusiv materialelor PLF menționate mai sus. `README.md` este păstrat și conține nota originală.

## Starea curentă observată

Inventar verificat la 7 octombrie 2026; existența unui fișier nu implică verificarea integrală a conținutului său.

| Zonă | Ce există | Stare observată |
| --- | --- | --- |
| `Curs/` | Materiale PDF pentru cursurile 1–3 și bibliografie | Recursivitate, introducere în Prolog, predicate deterministe și nedeterministe. |
| `Demo/` | Exemple SWI-Prolog și CLisp | Materiale didactice, supuse notei din README. |
| `Laborator/Descriere&Cerinte.pdf` | Cerințele disciplinei și ale lucrărilor | Secțiunea VIII.2 a fost citită în această discuție. |
| `Laborator/Lab01/` | `ex.pl`, enunțul R1 și exemple recursive C++/Python | `ex.pl` conține relații de familie; execuția nu a fost verificată. |
| `Laborator/Lab02/` | `P1.pdf`, `Lab02.pl` | `Lab02.pl` conține `substitute/4` pentru problema 12 a), fără documentația și exemplele cerute în fișier. |

## P1, problema 12 — context pentru continuare

- **a)** Substituirea unui element cu altul într-o listă. Soluția discutată înlocuiește toate aparițiile, păstrând ordinea și lungimea listei.
- **b)** Construirea sublistei `[l_m, ..., l_n]` din `[l_1, ..., l_k]`. Modelul discutat folosește poziții de la 1 și limite incluse, cu `1 <= m <= n <= k`. Codul pentru b) nu a fost furnizat în discuție.
- Codul observat pentru a) este `substitute(L, E, V, R)`: `L` este lista inițială, `E` elementul înlocuit, `V` înlocuitorul și `R` lista rezultat. În răspunsurile din chat s-a folosit numele românesc `substituie/4` pentru același predicat.
- Modele de flux: `(i, i, i, o)` și `(i, i, i, i)`. Intrările sunt presupuse complet instanțiate, adică fără variabile nelegate, inclusiv în interiorul termenilor.
- Model recursiv: pentru lista vidă rezultatul este `[]`; pentru `[H|T]`, se pune `V` în capul rezultatului dacă `H` este egal cu `E`, altfel se păstrează `H`, apoi se continuă cu `T`.
- Implementarea actuală folosește `H == E` și `H \== E`. Acestea compară identitatea termenilor fără să lege variabile. `H = E` unifică termenii, iar `H \= E` verifică imposibilitatea unificării. Pentru intrări complet instanțiate, perechile au același efect; varianta cu `=` și `\=` a fost prezentată ca alternativă conform exemplului de seminar.
- Unificarea și instanțierea au fost explicate prin exemple simple și prin potrivirea apelului cu antetul `[H|T]`. Utilizatorul urmărește înțelegerea conceptelor, nu doar obținerea codului.
- Utilizatorul a cerut specificații în formatul din imaginea de seminar: `% el = integer`, `% list = el*`, semnătura cu tipuri, modelele de flux și câte un comentariu pentru semnificația fiecărui argument. Cu `el = integer`, specificația descrie liste de întregi, deși codul poate compara și alți termeni complet instanțiați.

## Cerințe pentru documentarea soluțiilor

Conform secțiunii VIII.2 din `Laborator/Descriere&Cerinte.pdf`, o lucrare Prolog include modele recursive, modelele de flux ale predicatelor folosite, semnificația argumentelor, codul sursă și exemple care acoperă cât mai multe cazuri. Documentația poate fi inclusă în comentarii sau într-un document separat. Mediul indicat este SWI-Prolog.

Pentru a), în chat au fost date exemple pentru lista vidă, apariții multiple, element absent, toate elementele înlocuite, înlocuitor identic și verificarea unui rezultat corect/incorect. Aceste exemple nu sunt încă incluse în `Lab02.pl` și nu au fost executate în această sesiune.

## Ultima sesiune

- **Data:** 7 octombrie 2026.
- **Proiect sursă și cale:** PLF, `E:\Facultate\UBB\Sem. 3\PLF`.
- **Obiectiv:** crearea unui handoff similar celui din MAP, cu contextul discuției și informațiile din README.
- **Realizat:** creat acest document; inclusă nota despre exemplele didactice, starea fișierelor și contextul problemei P1/12.
- **Fișiere modificate:** `HANDOFF.md` (nou).
- **Verificări:** citite handoff-ul MAP, README-ul PLF și sursele curente `Lab02.pl` și `ex.pl`; documentul verificat după scriere. Nu s-a executat cod Prolog.
- **Decizii relevante:** README-ul și sursele au fost păstrate; soluțiile explicate în chat sunt diferențiate de ceea ce există efectiv în fișiere.
- **Probleme / informații lipsă:** documentația și exemplele de testare pentru a) lipsesc din sursa actuală; b) nu este implementat în fișierul observat.
- **Următorul pas concret:** la continuarea laboratorului, documentarea lui `substitute/4` în formatul cerut și verificarea exemplelor în SWI-Prolog; apoi abordarea subpunctului b), după cererea utilizatorului.

## Model pentru actualizări viitoare

Actualizează starea curentă și înlocuiește secțiunea „Ultima sesiune” cu datele reale. Păstrează un istoric scurt numai când ajută continuarea.

```text
Data:
Proiect sursă și cale:
Obiectiv:
Realizat:
Fișiere modificate:
Verificări și rezultate:
Decizii relevante:
Probleme / informații lipsă:
Următorul pas concret:
```

## Istoric scurt

- 2026-10-06–2026-10-07 — Discutate modelele pentru P1/12, codul pentru a), formatul specificației, unificarea și instanțierea; soluțiile și exemplele au fost prezentate în chat.
- 2026-10-07 — Creat handoff-ul PLF pe baza modelului MAP și a stării curente a proiectului.
