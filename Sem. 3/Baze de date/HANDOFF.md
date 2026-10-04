# Baze de date — predare între proiectele locale

Ultima actualizare: 4 octombrie 2026  
Folder sursă: `C:\Users\tudor\Documents\UBB\Sem. 3\Baze de date`  
Proiect de referință pentru format: `C:\Users\tudor\Documents\UBB\Sem. 3\MAP\HANDOFF.md`.

## Scop și utilizare

Acest document transmite contextul necesar continuării lucrului între proiectele locale. La începutul unei sesiuni, citește documentul și verifică fișierele relevante. La final, actualizează starea observată și secțiunea „Ultima sesiune” cu acțiunile efectiv realizate și verificările efectuate.

Din alt proiect, consultă originalul din folderul Baze de date. Dacă folosești o copie, precizează data și calea sursei și reconciliază ulterior diferențele. Documentul nu sincronizează automat fișierele și nu trimite mesaje altor proiecte. MAP este referința de format; nu a fost stabilit drept singurul proiect destinatar. Handoff-ul MAP conține o cale istorică pe unitatea E:, diferită de calea de la care a fost citit în această sesiune.

## Reguli de colaborare stabilite de utilizator

- Comunicăm în română; numele tabelelor, coloanelor și constrângerilor sunt în engleză.
- Nu modifica fișiere fără aprobarea explicită a utilizatorului. Pentru schimbări de cod, prezintă mai întâi planul și codul în chat, înainte de aplicare.
- Cererea de creare a acestui handoff autorizează acest document; nu autorizează modificări ale scripturilor SQL.
- Respectă cerințele PDF-ului de laborator și principiile/exemplele PDF-urilor de curs. La inventarierea actuală nu există PDF-uri de curs în folder; nu pretinde că au fost consultate.
- Nu folosi prefixul `dbo.` în codul prezentat utilizatorului.
- Denumește explicit constrângerile: `PK_`, `FK_`, `UQ_`, `CK_`. Folosește `GO` pe linie separată.
- Nu executa scripturi în SQL Server și nu șterge tabele fără autorizarea corespunzătoare. Până acum, conversația a furnizat cod pentru executare de către utilizator.

## Cerințe și fișiere disponibile

| Fișier | Rol și stare observată |
| --- | --- |
| `Laborator/Lab01/Lab 1 - ProiectareBazaDeDate.pdf` | Cerințele laboratorului 1, citite anterior în această conversație. |
| `Laborator/Lab01/Lab01.sql` | Scriptul aplicației de gestiune jocuri video; citit integral la 4 octombrie 2026. Conține 17 instrucțiuni CREATE TABLE. |
| `Seminar/Seminar01/Seminar 1.sql` | Exemplul Blog224: PK simple, FK și tabel de legătură cu PK compusă. Citit în această sesiune. |

Laboratorul cere proiectarea și implementarea unei aplicații simple în Microsoft SQL Server, minimum 10 tabele, cel puțin o relație 1–M și una M–N. Tema și o scurtă descriere trebuie transmise asistentului înainte de proiectare; transmiterea nu a fost confirmată în conversație. Durata indicată: două săptămâni.

Tema aleasă: aplicație de gestiune și distribuție a jocurilor video, similară Steam, cu utilizatori, catalog, cumpărături, colecții, recenzii, realizări, sesiuni de joc și prietenii. Utilizatorul a cerut 10 tabele principale plus tabelele intermediare.

## Starea curentă observată

Baza de date se numește `LaboratorGestiuneJocuri`; utilizatorul a declarat că a creat-o deja. Scriptul începe cu `USE LaboratorGestiuneJocuri;` și nu creează baza de date.

Toată schema discutată este prezentă în `Lab01.sql`. Nu a fost verificată prin conectare sau execuție în SQL Server. Nu este confirmată starea actuală a datelor: utilizatorul a spus că tabelele erau nepopulate înainte de recrearea primelor tabele, dar nu există o verificare recentă.

### Inventarul celor 17 tabele

Identificatorii PK simpli sunt `INT IDENTITY(1,1)`. Câmpurile sunt obligatorii, exceptând cele marcate NULL. Datele de creare/adăugare/deblocare/început au DEFAULT `SYSDATETIME()`.

| Tabel | Câmpuri | Chei și reguli relevante |
| --- | --- | --- |
| Users | user_id, username, email, password_hash, registered_at | PK user_id; UQ username și email; email NVARCHAR(254), password_hash VARCHAR(255). |
| Games | game_id, title, description NULL, release_date NULL, price | PK game_id; price DECIMAL(10,2), CK price >= 0; titlul nu este unic. |
| Genres | genre_id, name | PK genre_id; UQ name. |
| Platforms | platform_id, name | PK platform_id; UQ name. |
| Companies | company_id, name, country NULL, website NULL | PK company_id; înlocuiește Developers și Publishers. |
| Achievements | achievement_id, game_id, name, description NULL | PK achievement_id; FK game_id → Games; UQ (game_id, name). |
| Reviews | review_id, user_id, game_id, rating, content NULL, created_at | PK review_id; FK către Users și Games; UQ (user_id, game_id); CK rating între 1 și 10. |
| Orders | order_id, user_id, ordered_at, status | PK order_id; FK către Users; DEFAULT pending; CK status în pending/completed/cancelled. |
| Collections | collection_id, user_id, name, created_at | PK collection_id; FK către Users; UQ (user_id, name); UQ (collection_id, user_id). |
| GameSessions | session_id, user_id, game_id, started_at, ended_at NULL | PK session_id; FK compus (user_id, game_id) → UserGames; CK ended_at IS NULL OR ended_at >= started_at. |
| GameCompanies | game_id, company_id, role | PK (game_id, company_id); FK către Games și Companies; CK role în developer/publisher. |
| GameGenres | game_id, genre_id | PK (game_id, genre_id); FK către Games și Genres. |
| GamePlatforms | game_id, platform_id | PK (game_id, platform_id); FK către Games și Platforms. |
| UserAchievements | user_id, achievement_id, unlocked_at | PK (user_id, achievement_id); FK către Users și Achievements. |
| OrderItems | order_id, game_id, purchase_price | PK (order_id, game_id); FK către Orders și Games; purchase_price DECIMAL(10,2), CK >= 0. |
| UserGames | user_id, game_id, collection_id, added_at | PK (user_id, game_id); FK către Users și Games; FK compus (collection_id, user_id) → Collections(collection_id, user_id). |
| Friendships | user_id_1, user_id_2, requested_by, status, requested_at, responded_at NULL | PK (user_id_1, user_id_2); cele trei câmpuri de utilizator au FK către Users; reguli detaliate mai jos. |

În clasificarea folosită în conversație: primele 10 sunt tabele principale, ultimele 7 sunt tabele de legătură/asociere. Scriptul SQL este sursa exactă pentru tipurile și lungimile tuturor câmpurilor.

### Decizii de proiectare de păstrat

- `GameCompanies.role` NU face parte din PK, la cererea explicită a utilizatorului. O pereche joc–companie are un singur rol. Schema actuală nu permite ambele roluri simultan pentru aceeași pereche.
- `Platforms` și `GamePlatforms` au fost păstrate: un joc poate rula pe mai multe platforme. S-a discutat reducerea lor, dar nu a fost adoptată.
- `Library` a fost redenumit în `UserGames` (numele final, la plural).
- Fiecare colecție aparține unui singur utilizator. Fiecare joc deținut aparține exact unei colecții a acelui utilizator; aceeași deținere nu poate apărea simultan în două colecții.
- PK (user_id, game_id) din UserGames împiedică duplicarea deținerii între colecțiile aceluiași utilizator. FK compus către Collections verifică proprietarul colecției. UQ (collection_id, user_id) din Collections permite acest FK.
- `GameSessions` are o singură relație directă, către UserGames, prin FK compus. user_id și game_id se pot repeta între sesiuni; session_id identifică fiecare sesiune.
- `playtime` și `last_played` nu sunt stocate în UserGames. Se calculează din GameSessions; ultima accesare a fost definită în discuție ca cel mai recent started_at. Durata totală se calculează pentru sesiunile încheiate.
- Games → Achievements este 1–M. Users ↔ Achievements este M–N prin UserAchievements.
- Users → Orders este 1–M; Orders ↔ Games este M–N prin OrderItems. purchase_price păstrează prețul istoric; totalul comenzii se calculează. Nu există cantitate: un joc apare cel mult o dată într-o comandă.
- OrderItems reprezintă cumpărăturile, UserGames reprezintă deținerea. Finalizarea unei comenzi nu inserează automat jocurile în UserGames; scriptul nu conține această logică.
- Friendships păstrează user_id_1 < user_id_2, prevenind relațiile cu sine și duplicatele inverse. requested_by trebuie să fie unul dintre cei doi utilizatori. status are DEFAULT pending și CK cu pending/accepted/rejected/cancelled. responded_at poate fi NULL sau >= requested_at.
- Nu s-au adăugat reguli care să oblige recenzentul sau utilizatorul unei realizări să dețină jocul. FK actuale din Reviews și UserAchievements nu verifică acest lucru.

## Ultima sesiune

- **Data:** 4 octombrie 2026.
- **Proiect sursă:** Baze de date, la calea indicată la început.
- **Obiectiv:** creare handoff în rădăcină, similar documentului MAP, pentru transfer de context între proiectele locale.
- **Realizat:** citirea handoff-ului MAP, inventarierea fișierelor, citirea scripturilor SQL și documentarea schemei și deciziilor din conversație.
- **Fișiere modificate:** `HANDOFF.md` (nou). Niciun script SQL modificat; handoff-ul MAP nu a fost modificat.
- **Verificări:** schema de 17 tabele este prezentă în Lab01.sql; ordinea din fișier plasează tabelele referite înaintea celor dependente. Nu s-a executat SQL, nu s-a inspectat o bază de date live și nu s-au rulat teste.
- **Informații lipsă:** confirmarea execuției integrale în SQL Server, starea actuală a datelor, confirmarea transmiterii temei către asistent și PDF-urile de curs.
- **Următorul pas concret:** la cererea utilizatorului, confruntarea listei de tabele și constrângeri existente în SQL Server cu Lab01.sql. Popularea, verificările prin date și alte modificări de cod necesită stabilirea scopului și aprobarea utilizatorului.

## Model pentru actualizări viitoare

Actualizează secțiunea „Ultima sesiune” și starea curentă pe baza acțiunilor reale. Separă observațiile din fișiere de informațiile declarate de utilizator și de verificările efectuate în SQL Server.

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

- 2026-10-04 — Handoff inițial creat în rădăcina Baze de date; schema din fișier inventariată, fără modificări de cod sau execuție în SQL Server.
