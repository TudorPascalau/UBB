# Handoff — Rețele de calculatoare (RC)

Actualizat: 13 octombrie 2026. Rezumat reconstruit din fișierele actuale și istoricul Git; conversațiile de pe celălalt calculator nu sunt disponibile.

## Rezumatul lucrărilor

- Organizate materialele în `Curs/`, `Laborator/` și `Socket/`.
- Păstrate cursurile 1 și 2 în PDF și materialul introductiv `Laborator/Lab01/socket.pdf`.
- Adăugate exemplele client/server din `Laborator/Lab02`, în C și Python.
- Adăugat exemplul rezolvat de sumă a două numere în `Socket/Rezolvata`, în C.
- Implementată `Socket/Problema01`: clientul trimite două numere, serverul întoarce suma; variante C și Python.
- Implementată `Socket/Problema02`: clientul trimite un șir, serverul întoarce numărul de spații; variante C și Python.
- Reorganizate exercițiile din vechiul director `Probleme socket/` în `Socket/`; vechile copii au fost eliminate.

## Fișiere importante

| Locație | Conținut / comportament actual |
| --- | --- |
| `Curs/` | PDF-uri pentru cursurile 1 și 2 |
| `Laborator/Lab01/socket.pdf` | Material de laborator despre socket-uri |
| `Laborator/Lab02/client.c`, `server.c` | Trimiterea unui `int` și returnarea lui către client |
| `Laborator/Lab02/client.py`, `server.py` | Exemplu Python 2: trimiterea și afișarea unui număr, fără răspuns către client |
| `Socket/Rezolvata/client.c`, `server.c` | Exemplu de sumă, TCP, port 1234, numere pe 16 biți |
| `Socket/Problema01/client.c`, `server.c` | Sumă, TCP, port 1234, protocol binar pe 16 biți |
| `Socket/Problema01/client.py`, `server.py` | Sumă, TCP, port 1234, protocol text, Python 3 |
| `Socket/Problema02/client.c`, `server.c` | Numărarea spațiilor, TCP, port 8080, răspuns binar pe 16 biți |
| `Socket/Problema02/client.py`, `server.py` | Numărarea spațiilor, TCP, port 8080, răspuns text, Python 3 |

În cele trei directoare din `Socket/` există și `client.exe` / `server.exe`, urmărite în Git. Existența acestora nu confirmă că sunt sincronizate cu sursele sau că rulează pe Windows.

În sesiunea de handoff s-a adăugat doar `HANDOFF.md`; sursele și materialele nu au fost modificate.

## Detalii tehnice și convenții

- Exerciții independente, fiecare cu propriul client și server; nu există o infrastructură comună de build sau teste în RC.
- Comunicare IPv4 prin TCP (`AF_INET`, `SOCK_STREAM`); serverele prelucrează clienții secvențial.
- Problema01 în C folosește `uint16_t`, `htons` și `ntohs`; varianta Python folosește text. Clientul C și serverul Python nu au același protocol, nici invers.
- Problema02 are, de asemenea, protocoale diferite în C și Python. Răspunsul C este trimis în ordinea de octeți a gazdei, fără conversie de rețea.
- Sursele C folosesc API POSIX și antete Unix; compilarea trebuie verificată într-un mediu compatibil, de exemplu Linux/WSL. Exemplele Lab02 includ instrucțiuni de compilare cu `gcc` și rulare în două terminale.
- Acestea sunt observații din implementare, nu decizii de proiect confirmate prin conversații anterioare. Păstrați structura existentă la continuare.

## Starea actuală și probleme cunoscute

Implementările sunt prezente, dar în această sesiune nu s-au compilat și nu s-au rulat programele. Nu există teste automate în folderul RC. Commitul care marchează Problema02 drept terminată nu garantează corectitudinea tuturor cazurilor.

- **Problema02 C:** serverul ignoră numărul de octeți returnat de `recv`, apoi apelează `strlen` pe un buffer fără terminator NUL garantat. Poate citi dincolo de datele primite; aceasta este prioritatea de corectare.
- **Problema02 Python:** clientul citește numai doi octeți pentru răspunsul text. Un rezultat de 100 sau mai multe spații poate fi trunchiat; chiar și un răspuns mai scurt poate ajunge fragmentat.
- **Citire/scriere TCP:** mai multe exemple presupun că un singur `send`/`recv` transferă întregul mesaj. Lipsesc tratarea completă a transferurilor parțiale, delimitarea mesajelor text și verificarea consecventă a erorilor/deconectărilor.
- **Adrese C:** clienții din Problema01 și Problema02 folosesc `INADDR_ANY` ca destinație; pentru conectare locală trebuie preferată o adresă explicită precum `127.0.0.1`.
- **Lab02 C:** portul este atribuit direct ca `8888`, fără `htons`; pe sisteme little-endian nu corespunde portului Python 8888. Sunt trimise valori `int` în reprezentarea nativă, iar antetele pentru unele funcții sunt incomplete.
- **Lab02 Python:** folosește sintaxa Python 2, incompatibilă cu Python 3 fără adaptare; serverul nu închide conexiunea după fiecare client în bucla normală.
- **Suma C:** rezultatul este stocat pe 16 biți; sumele peste 65535 se reduc modulo 65536. Intervalul acceptat și comportamentul la depășire nu sunt validate explicit.

## Pași următori

1. Corectarea citirii bufferului și a terminării șirului în serverul C pentru Problema02.
2. Stabilirea unei delimitări clare a mesajelor și citirea integrală a răspunsului Python pentru Problema02.
3. Verificarea ambelor probleme în C și Python: cazuri obișnuite, șir fără spații, multe spații, valori-limită și deconectări.
4. Dacă se dorește interoperabilitate C/Python, definirea explicită a unui protocol comun; în prezent se folosesc perechi din aceeași variantă.
5. La reluarea Lab02, adaptarea exemplului Python la Python 3 și corectarea portului/antetelor în C.

Nu există în contextul disponibil o cerință confirmată pentru un exercițiu nou; pașii de mai sus provin din verificarea surselor.

## Stare Git

- Repository-ul este la `E:\Facultate\UBB`, iar RC este subdirectorul `Sem. 3/RC`; RC nu are repository separat.
- Branch verificat: `main`, cu upstream `origin/main`. Înainte de crearea acestui document, `git status` era curat și nu indica diferență de commituri față de referința locală `origin/main`. Nu s-a făcut fetch; starea serverului GitHub nu a fost verificată.
- HEAD: `b759693` — `RC: Finished socket Problem02`.
- Commituri recente relevante, toate din 13 octombrie 2026:
  - `e25a41d`: eliminarea copiilor din vechea structură `Probleme socket/`.
  - `f10c32f`: adăugarea structurii `Socket/` și reorganizarea exercițiilor.
  - `d08c632`: varianta Python pentru Problema01.
  - `a829364`: variantele C pentru sumă și exemplul rezolvat.
  - `7bef8ce`: exemplele Lab02.
- Modificare a acestei sesiuni: `Sem. 3/RC/HANDOFF.md`, fișier nou, necomis. Nu s-a făcut commit sau push.

## Context pentru următoarea sesiune

Proiectul este lucrat pe laptop și desktop, cu istorii de conversație independente. Citiți acest document la început și verificați sursele și Git înainte de modificări. Codul și istoricul Git au prioritate față de handoff. Actualizați documentul când utilizatorul cere „handoff”, „changelist” sau „session summary”; nu după fiecare schimbare. Nu faceți commit sau push fără cerere explicită și nu includeți informații sensibile.
