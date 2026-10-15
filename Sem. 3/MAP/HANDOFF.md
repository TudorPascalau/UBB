# MAP — predare între proiectele locale

Ultima actualizare: 15 octombrie 2026  
Folder MAP curent: `C:\Users\tudor\Documents\UBB\Sem. 3\MAP`  
Folder MAP anterior, menționat în istoricul proiectului: `E:\Facultate\UBB\Sem. 3\MAP`  
Celălalt proiect local: numele și calea nu au fost încă precizate.

## Scop și utilizare

Acest fișier este punctul comun de context pentru continuarea lucrului din MAP sau din celălalt proiect local. La începutul unei sesiuni, citește acest document și verifică fișierele relevante. La final, actualizează secțiunea „Ultima sesiune” cu ce s-a realizat efectiv, verificările făcute și următorul pas.

Din celălalt proiect, folosește fișierul din folderul MAP curent indicat mai sus, dacă ai acces. Dacă lucrezi cu o copie, precizează data și proiectul sursă și reconciliază modificările cu originalul. Documentul transmite context; nu sincronizează automat codul și nu pornește comunicarea între proiecte.

## Reguli de colaborare

- Nu modifica fișiere fără aprobarea explicită a utilizatorului. Pentru schimbări de cod, prezintă mai întâi planul și codul în chat și așteaptă aprobarea aplicării.
- Folosește cerințele PDF ale laboratorului și principiile și exemplele din PDF-urile de curs.
- Cererea din 15 octombrie de actualizare a acestui handoff autorizează modificarea documentului, nu remedieri suplimentare în cod.

## Starea curentă observată

Inventarul inițial este din 3 octombrie 2026; starea laboratorului de rețea de socializare a fost actualizată prin citirea surselor la 15 octombrie 2026. Observațiile vechi despre celelalte proiecte trebuie reverificate înainte de continuare.

| Zonă | Ce există | Stare observată |
| --- | --- | --- |
| `Curs` | `curs1.pdf` | Material de curs; conținutul nu a fost analizat în această sesiune. |
| `Laborator/Lab01` | Clasele `Car`, `AudiCar`, `PorscheCar`, `Application`; `exemplu.mdj` | Exemplu Java de moștenire și polimorfism. |
| `Laborator/Lab02` | `Lab1_2026-2027.pdf` și proiectul `Laborator02` | Calculator de expresii cu numere complexe, organizat în `model`, `expression` și `parser`. |
| `Laborator/Lab03` | Cerințele rețelei de socializare și proiectul `Laborator03` | Domain, validatori, repository-uri în memorie și CSV, service și UI cu meniu; lipsește încă punctul de pornire `Main`. |
| `Seminar/Seminar 1` | `Task`, `MessageTask`, `Container`, `StackContainer`, `Main` | Implementare în lucru; `Main` și `StackContainer` conțin cod incomplet. |

### Laborator 02 — context pentru continuare

- `ComplexNumber` are câmpuri finale și operații de adunare, scădere, înmulțire și împărțire; împărțirea la zero aruncă o excepție.
- `ComplexExpression` evaluează operanzii succesiv, de la stânga la dreapta. Clasele derivate implementează cele patru operații, iar `ExpressionFactory` selectează expresia.
- `CommandLineExpressionParser` citește argumentele în alternanță număr/operator și cere ca toți operatorii să fie identici.
- `ComplexNumberParser` folosește o expresie regulată și elimină spațiile dintr-un număr.
- De verificat: coeficientul imaginar omis în forme precum `1+i` este tratat în codul actual ca `0.0`; dacă forma este acceptată, coeficientul așteptat este `1.0`. Gruparea alternativelor din expresia regulată merită verificată pentru semne și zecimale.
- Cerințele din PDF nu au fost confruntate cu implementarea. Compilarea și execuția nu au fost verificate în această sesiune.

### Seminar 1 — lucru rămas vizibil

- Completarea instrucțiunii `MessageTask task1 =` din `Main`.
- Implementarea metodelor `remove`, `add`, `size` și `get` din `StackContainer`.
- Corectarea referințelor `Tasks` la câmpul `tasks` și eliminarea fragmentului izolat `T`.
- Clarificarea utilizării parametrului de capacitate din constructorul `StackContainer`.

## Ultima sesiune

- **Data:** 15 octombrie 2026.
- **Proiect sursă și cale:** MAP, `C:\Users\tudor\Documents\UBB\Sem. 3\MAP`.
- **Obiectiv:** continuarea rețelei de socializare după implementarea service-ului; UI minimalist, ID-uri automate și persistență CSV.
- **Realizat și confirmat în surse:**
  - `SocialNetworkService` oferă adăugare/ștergere/listare pentru utilizatori și prietenii. Ștergerea unui utilizator elimină și prieteniile sale.
  - `addUser(String firstName, String lastName)` generează ID-ul în service. Contorul pornește de la 1 sau peste cel mai mare ID din repository și crește după salvarea reușită. UI-ul nu mai solicită ID la adăugarea utilizatorului.
  - `UserInterface` are opțiunile 1–6 pentru operațiile existente și 0 pentru ieșire. Folosește `Scanner.nextLine()`, conversie numerică pentru ID-urile introduse și tratarea `NumberFormatException`, `ValidationException` și `ServiceException`.
  - Afișarea utilizatorilor și prieteniilor folosește `System.out.println(entity)`, deci `toString()`, fără apelarea getterelor din UI. `User.toString()` include deja ID-ul.
  - Sunt prezente `AbstractFileRepository`, `UserFileRepository`, `FriendshipFileRepository` și `RepositoryException`. Codul pentru acestea a fost propus în chat și ulterior găsit implementat în workspace; nu a fost aplicat de agent în etapa propunerii.
  - Repository-ul abstract implementează direct `Repository`, încarcă și validează datele la inițializarea repository-urilor concrete și persistă modificările printr-un fișier temporar înainte de actualizarea hărții din memorie.
  - Constructorul abstract primește acum `String` și îl convertește cu `Path.of(file).toAbsolutePath()`. Constructorii concreți pot apela `super(fileName, validator)` fără conversie suplimentară; neconcordanța String/Path discutată nu mai apare în sursele citite.
- **Format CSV:** UTF-8, fără antet; utilizatori: `id,firstName,lastName`; prietenii: `firstUserId,secondUserId`. Format simplificat, fără suport pentru câmpuri citate; la salvarea numelor sunt respinse virgulele, ghilimelele și liniile noi.
- **Modificări aplicate de agent în cod în această conversație:** `SocialNetworkService.java` și `UserInterface.java`, din `Laborator/Lab03/Laborator03/src`. `User.toString()` includea deja ID-ul, deci nu a necesitat schimbare. Actualizarea curentă modifică doar `HANDOFF.md`.
- **Verificări efectuate anterior adăugării claselor CSV:** compilare reușită cu JDK 21; verificări temporare pentru inițializarea ID-ului peste date existente, păstrarea contorului după validare eșuată și ștergere, adăugare/listare/ștergere din UI pentru utilizatori și prietenii și tratarea unui ID nenumeric. Verificările au trecut. Aceste rezultate nu certifică repository-urile CSV adăugate ulterior.
- **Starea verificărilor CSV:** clasele au fost citite la actualizarea handoff-ului; nu s-au executat compilare sau teste de persistență/reîncărcare pentru versiunea curentă cu CSV.
- **Lucru rămas / observații de verificat, fără remedieri aplicate:**
  - Nu există `Main.java` în `Laborator03/src`; trebuie construit punctul de pornire cu cele două repository-uri CSV, service și UI. Căile `data/users.csv` și `data/friendships.csv` au fost propuse în chat, dar nu sunt încă legate într-un punct de pornire.
  - UI-ul nu tratează încă `RepositoryException`; integrarea a fost propusă, nu aplicată.
  - În `loadFromFile()`, ID-urile duplicate aruncă `IllegalStateException`, dar blocul catch tratează `IllegalArgumentException | ValidationException`. Eroarea de duplicat nu este împachetată cu fișierul și numărul liniei.
  - `InMemoryRepository.update()` întoarce entitatea și la succes, în timp ce repository-ul cu fișier întoarce `null` la succes. Trebuie clarificat și uniformizat contractul.
  - Contorul ID nu este persistat separat: după repornire, ID-urile șterse peste maximul rămas pot fi reutilizate.
  - Ștergerea utilizatorului și a prieteniilor implică mai multe salvări; nu există tranzacție comună între cele două fișiere. Integritatea referințelor către utilizatori la încărcarea prieteniilor nu este încă verificată de service.
  - Mai lipsesc funcționalitățile cerute pentru numărul de comunități și comunitatea cea mai sociabilă, precum și verificarea/completarea JavaDoc.
- **Materiale consultate:** `Laborator/Lab03/Lab2_2026-2027.pdf`, `Laborator/Lab03/Enunt Proiect Lab - Retea de socializare.pdf`, secțiuni relevante din `Curs/curs1.pdf` și `Curs/Curs02/curs2.pdf`. Cerințele permit UI minimalist și persistență în memorie sau fișier; cursul 1 prezintă SRP și `switch` clasic.
- **Următorul pas concret:** prezintă spre aprobare codul de integrare CSV în `Main` și tratarea `RepositoryException` în UI; după aprobare, aplică și verifică salvarea/reîncărcarea utilizatorilor și prieteniilor. Prezintă separat eventualele corecții de repository înainte de aplicare.

## Sesiunea precedentă — 6 octombrie 2026

- **Data:** 6 octombrie 2026.
- **Proiect sursă:** MAP.
- **Obiectiv:** mutarea construirii expresiilor din Operation în DefaultExpressionFactory și documentarea posibilității unui registru.
- **Realizat:** Operation păstrează constantele, simbolurile și fromSymbol; DefaultExpressionFactory construiește expresiile prin switch clasic. README-ul explică limita OCP și un posibil registru ExpressionCreator[] compatibil cu restricțiile laboratorului. Diagrama UML nu a fost modificată.
- **Fișiere modificate:** Laborator/Lab02/Laborator02/src/model/Operation.java, Laborator/Lab02/Laborator02/src/expression/DefaultExpressionFactory.java, Laborator/Lab02/readme.txt și HANDOFF.md.
- **Verificări:** cerințele PDF confirmă interdicția colecțiilor generice predefinite și a facilităților Java 8. Compilare reușită cu JDK 21; rezultate verificate pentru toate cele patru operații și respingerea unui operator necunoscut. Operatorul * a fost transmis între ghilimele pentru a evita expandarea wildcard-ului pe Windows.
- **Decizii relevante:** switch-ul este acceptat pentru simplitate; fabrica și enum-ul necesită modificări la adăugarea operațiilor. Registrul bazat pe array este doar o extensie documentată, nu implementată.
- **Următorul pas:** sincronizarea diagramei UML prin eliminarea createExpression din Operation și reprezentarea dependențelor de creare ale fabricii către expresiile concrete.
## Model pentru actualizări viitoare

Înlocuiește secțiunea „Ultima sesiune” cu datele reale ale sesiunii încheiate. Actualizează și starea curentă dacă implementarea s-a schimbat. Păstrează mai jos un rezumat scurt al sesiunii precedente când este util.

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

- 2026-10-03 — Document inițial creat în rădăcina MAP; starea surselor inventariată, fără modificări de cod.
- 2026-10-04 — Completarea claselor și a enumerării din `Lab02.mdj` conform codului Java, fără relații.
- 2026-10-04 — Ajustarea relațiilor adăugate de utilizator, fără legături suplimentare ale fabricii către clasele concrete.
- 2026-10-04 — Verificarea variantei finale și a PDF-ului; compilare reușită, identificarea erorii pentru coeficientul imaginar omis și a elementelor UML rămase în model.
- 2026-10-06 — Ajustarea fabricii expresiilor și documentarea extensiei prin registru; detalii păstrate în secțiunea sesiunii precedente.
- 2026-10-15 — Rețea de socializare: ID-uri automate în service, meniu UI complet pentru operațiile existente și afișare prin `toString()`. Verificări reușite înainte de adăugarea CSV; clasele de persistență CSV sunt prezente, dar integrarea și verificarea lor rămân de făcut. Actualizat handoff-ul la cererea utilizatorului.




