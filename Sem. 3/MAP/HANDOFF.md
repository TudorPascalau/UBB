# MAP — predare între proiectele locale

Ultima actualizare: 29 octombrie 2026  
Folder MAP curent: `E:\Facultate\UBB\Sem. 3\MAP`  
Alt folder MAP menționat în istoric, neverificat în sesiunea curentă: `C:\Users\tudor\Documents\UBB\Sem. 3\MAP`  
Proiect activ: `Laborator/Lab04/SocialNetwork` (Gradle, surse în `src/main/java`).  
Celălalt proiect local: numele și calea nu au fost încă precizate.

## Scop și utilizare

Acest fișier este punctul comun de context pentru continuarea lucrului din MAP sau din celălalt proiect local. La începutul unei sesiuni, citește acest document și verifică fișierele relevante. La final, actualizează secțiunea „Ultima sesiune” cu ce s-a realizat efectiv, verificările făcute și următorul pas.

Din celălalt proiect, folosește fișierul din folderul MAP curent indicat mai sus, dacă ai acces. Dacă lucrezi cu o copie, precizează data și proiectul sursă și reconciliază modificările cu originalul. Documentul transmite context; nu sincronizează automat codul și nu pornește comunicarea între proiecte.

## Reguli de colaborare

- Nu modifica fișiere fără aprobarea explicită a utilizatorului. Pentru schimbări de cod, prezintă mai întâi planul și codul în chat și așteaptă aprobarea aplicării.
- Folosește cerințele PDF ale laboratorului și principiile și exemplele din PDF-urile de curs.
- Cererea din 15 octombrie de actualizare a acestui handoff autorizează modificarea documentului, nu remedieri suplimentare în cod.
- În conversația din 29 octombrie, utilizatorul a cerut explicații și fragmente de cod pentru a implementa personal schimbările. Continuă acest stil: verifică sursele și explică, fără aplicarea schimbărilor în cod până la o cerere explicită. Cererea curentă autorizează actualizarea acestui handoff.

## Starea curentă observată

Inventarul inițial este din 3 octombrie 2026. Starea proiectului activ Lab04 a fost actualizată prin citirea surselor la 29 octombrie 2026 și este descrisă în „Ultima sesiune”. Tabelul de mai jos este un inventar istoric; observațiile despre Lab03 și celelalte proiecte trebuie reverificate înainte de continuare și nu descriu starea Lab04.

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

- **Data și proiect:** 29 octombrie 2026, `E:\Facultate\UBB\Sem. 3\MAP\Laborator\Lab04\SocialNetwork`.
- **Obiectiv:** parcurgerea pedagogică a cerințelor Lab04 și refactorizarea soluției Lab03 cu interfețe funcționale, predicate, Optional și Stream API. PDF-ul de referință este `Laborator/Lab04/Lab4_2026-2027_InterfeteFunctionale.pdf`. Utilizatorul confirmă că proiectul este versionat în Git.
- **Autorizarea acestei actualizări:** modificarea `HANDOFF.md`; nu sunt autorizate prin această cerere remedieri în surse sau actualizarea readme-ului.

### Schimbări confirmate în sursele actuale

1. **Validatori:** `Validator<T>` are `@FunctionalInterface` și `default andThen(Validator<T>)`. Validatorul compus execută întâi strategia existentă, apoi regula suplimentară; la prima excepție se oprește. Un validator suplimentar null este respins imediat. În `Main`, o lambda limitează numele și prenumele la câte 100 de caractere și este compusă cu `UserValidator`; limita este demonstrativă, nu impusă de PDF. `UserValidator` acceptă acum și nume cu cratimă între grupuri de litere, prin regex-ul Java `"\\p{L}+(-\\p{L}+)*"`; cratimele inițiale/finale și cele consecutive sunt respinse.
2. **Filtrare:** `Repository.findAll()` rămâne `Iterable<E>`, prin decizia explicită a utilizatorului. Noua metodă default `List<E> findAll(Predicate<E>)` respinge predicatul null și construiește rezultatul cu `filter` și `collect(Collectors.toList())`. `service.UserCriteria` furnizează `lastNameEquals` și `firstNameEquals`, cu verificarea argumentelor și comparații case-insensitive. `SocialNetworkService.findUsers(Predicate<User>)` deleagă către repository.
3. **Meniu:** opțiunea 10 deschide filtrările după nume, prenume, AND, OR, negare prin `negate()` și `Predicate.not`. Rezultatele sunt afișate prin `forEach(System.out::println)`. Nu s-au introdus metode specifice precum `findByLastName` în repository.
4. **Optional:** contractele `findOne`, `save`, `update`, `delete` întorc `Optional<E>`, inclusiv în memoria internă, repository-ul abstract pe fișier și scheletele DATABASE. Javadoc-ul interfeței descrie noile rezultate. `findOne`/`delete`: empty înseamnă absent; valoarea prezentă este entitatea găsită/eliminată. `save`/`update`: empty înseamnă succes; valoarea prezentă este entitatea existentă la duplicat, respectiv entitatea propusă dacă ID-ul de actualizat lipsește. Verificările din încărcare/persistență și service au fost adaptate la `isPresent`, `isEmpty`, `orElseThrow`. Nu întoarce null în loc de Optional.
5. **Factory:** două `EnumMap` asociază `RepositoryType` cu `Function<Validator<...>, Repository<...>>`, pentru utilizatori și prietenii. Constructorul înregistrează funcțiile; metodele publice aleg funcția și execută `apply(validator)`. MEMORY folosește `InMemoryRepository::new`; FILE/DATABASE folosesc lambda-uri cu proprietățile necesare. Se construiește doar repository-ul selectat. Validarea configurației pentru backend-ul ales este păstrată. Supplier nu este necesar suplimentar: Function este alternativa acceptată de enunț.
6. **Template Method păstrat:** utilizatorul a ales explicit să mențină `AbstractFileRepository` și subclasele cu `extractEntity`/`createEntityAsString`, în locul unui repository generic parametrizat cu Function pentru conversii.
7. **Helper de stream:** clasa reală se numește `util.StreamHelper` (nu `Streams`, numele din exemplul inițial). `StreamHelper.stream(Iterable<T>)` centralizează singurul apel `StreamSupport.stream(source.spliterator(), false)`. Este importată static unde este folosită și întoarce de fiecare dată un stream secvențial nou.
8. **Service:** următorul ID se calculează prin `mapToLong(User::getId).max().orElse(0L) + 1`. Verificarea relațiilor încărcate folosește `flatMap` către cele două ID-uri și `forEach(this::ensureUserExists)`. Ștergerea utilizatorului selectează mai întâi prieteniile într-o listă, apoi le șterge și păstrează separat jurnalul ștergerilor reușite pentru rollback. `removed.add(...)` din `forEach` servește jurnalului operațional, nu construirii rezultatelor filtrării; explică această distincție la evaluare. `getMostSociableCommunity` extrage rezultatul cu `orElseThrow`. `getCommunityCount()` folosește încă `getCommunities().size()`; alternativa cu stream/count a fost propusă, dar nu este implementată.
9. **Fișiere:** citire cu `Files.lines` în try-with-resources, materializarea liniilor într-o listă și `IntStream.range` pentru numerele fizice ale liniilor. `loadLine` ignoră liniile goale, validează prin `super.save`, detectează duplicatele și raportează fișierul/linia/cauza. Sunt tratate IOException și UncheckedIOException și restaurată starea la eșec. Scrierea transformă entitățile prin `map(this::createEntityAsString)` și `collect`, apoi folosește `Files.write` în fișierul temporar; mutarea atomică și rollback-ul sunt păstrate. DATABASE rămâne schelet cu UnsupportedOperationException.
10. **Graful:** `FriendshipGraph` colectează ID-urile, validează referințele, produce cele două sensuri ale fiecărei prietenii cu `flatMap`, grupează vecinii prin `groupingBy`/`mapping`/`toSet` și construiește harta finală cu `toMap`. Include utilizatorii izolați și expune structuri nemodificabile.
11. **Comunitățile:** `findCommunities` utilizează colectare cu supplier/accumulator/combiner și o mulțime comună `visited`; DFS este acum recursiv prin `visitComponent`, cu vecinii procesați prin `filter` și `forEach`. Acest algoritm depinde de execuția secvențială; nu folosi parallelStream. Pentru comunitatea cea mai sociabilă, `map` asociază fiecare comunitate cu lungimea celui mai lung drum, calculată o singură dată; `max(Comparator.comparingInt(...))` alege scorul maxim și `map(Map.Entry::getKey)` extrage comunitatea.
12. **Bucle rămase:** `longestPathLength` și `longestPathFrom` păstrează buclele algoritmului de backtracking, inclusiv oprirea anticipată la n-1 muchii. S-a convenit păstrarea lor cu justificare în readme, conform excepției din PDF. `while (running)` din UI controlează meniul și nu parcurge o colecție.

### Explicații și decizii discutate

- Stream este un pipeline, nu o colecție; operațiile intermediare sunt leneșe, iar operația terminală declanșează prelucrarea. Un stream se consumă o singură dată.
- Predicate reprezintă o condiție `T -> boolean`; Collectors furnizează strategii de colectare. StreamSupport creează un stream dintr-un Spliterator, chiar și pentru procesare secvențială.
- Iterable a fost păstrat deliberat. List ar permite `.stream()` direct, dar ar restrânge contractul; implementarea actuală în memorie întoarce deja o copie ArrayList.
- Recomandarea PDF pentru comunități este respectată prin varianta DFS cu vecini procesați prin stream, nu prin atribuirea unui ID de componentă și groupingBy. `groupingBy` din FriendshipGraph grupează vecinii după utilizator, nu comunitățile. Cele două alternative din PDF nu sunt obligatorii simultan.
- Criteriul pentru comunitatea cea mai sociabilă rămâne lungimea celui mai lung drum simplu, nu numărul membrilor. Backtracking-ul poate fi foarte costisitor; DFS recursiv poate depăși stiva pentru grafuri foarte adânci.

### Verificări și limite

- La actualizarea curentă s-au citit sursele pentru confirmarea implementării; nu s-au compilat și nu s-au executat teste pentru versiunea completă după refactorizarea cu stream-uri. Nu considera confirmarea structurală o validare completă a laboratorului.
- La începutul conversației, etapa Validator a fost compilată direct cu JDK 21 și verificată printr-un program temporar: compunere, oprire după eșec, validator null; o intrare de 101 caractere a fost respinsă din UI. Acele verificări nu certifică schimbările ulterioare.
- Gradle a întâmpinat acces refuzat la fișierul de lock din cache-ul utilizatorului. JDK-ul folosit cu succes direct: `C:/Program Files/Java/jdk-21.0.12/bin`. Java din PATH a rămas blocat în încercările inițiale; folosește calea explicită dacă problema reapare.
- Unele colectări actuale folosesc `Stream.toList()` (Java 16+), deși materialul și cerința de colectare insistă pe `collect(Collectors.toList())`. Proiectul folosește și alte API-uri ulterioare Java 8; nu presupune că trebuie convertit integral la Java 8. Verifică separat respectarea cerinței pedagogice pentru collect.
- Citirea tuturor liniilor înainte de validare schimbă prioritatea erorilor în cazul rar al unei linii invalide urmate de o eroare fizică de citire; acest detaliu a fost explicat, nu testat.

### Ce rămâne de făcut

1. Compilează și verifică versiunea actuală pe date temporare: rețea goală, utilizatori izolați, componente multiple, lanț versus stea, filtrări simple/compuse, duplicate, fișier lipsă, linii corupte cu număr fizic corect, reîncărcare și ștergere în cascadă; verifică și rollback-ul la erori de persistență. Nu modifica datele utilizatorului pentru teste.
2. Actualizează `Laborator/Lab04/readme.txt`: încă are explicații despre switch și convențiile null din Lab03. Documentează Optional, Function în factory, păstrarea Template Method, criteriile, helper-ul, minimum cinci bucle înainte/după și justificarea buclelor de backtracking. Această actualizare nu a fost aplicată prin cererea pentru handoff.
3. Auditează cerințele încă neacoperite explicit: prietenii unui utilizator în service, operațiile Stream API și colectorii enumerați în PDF, sortări cu Comparator și toate cele patru forme de referințe la metode. Nu declara laboratorul complet pe baza refactorizării de până acum.
4. Revizuiește lambda-urile care doar apelează metode: de exemplu, `entry -> entry.getKey()`, `entry -> entry.getValue()` și combiner-ul `left.addAll(right)` pot deveni referințe la metode acolo unde inferența tipurilor permite.
5. Curăță documentația: comentariul `DFS with stack` din CommunityAnalyzer este depășit după trecerea la recursivitate; descrierea clasei UserValidator trebuie să menționeze și cratimele. Verifică Javadoc/doclint pentru metodele noi și pregătește cel puțin trei exemple înainte/după pentru demonstrație.
- **Următorul pas concret:** verificarea compilării și a comportamentului codului actual, apoi compararea cerințelor PDF cu implementarea și completarea documentației. Continuă să oferi explicații și cod în chat înainte de orice modificare în surse.

## Sesiunea anterioară — tratarea erorilor în UI

- **Data și proiect:** 21 octombrie 2026, `E:\Facultate\UBB\Sem. 3\MAP`.
- **Obiectiv autorizat:** tratarea IllegalArgumentException în UI.
- **Modificări:** UserInterface.run prinde IllegalArgumentException după NumberFormatException și afișează un mesaj distinct, apoi continuă meniul. start păstrează tratarea erorilor de inițializare, dar apelează run în afara blocului try de inițializare.
- **Verificări:** compilare JDK 21; test temporar cu service care aruncă IllegalArgumentException, intrare nenumerică și o operație ulterioară. Mesajele distincte și continuarea meniului au fost confirmate. Datele proiectului nu au fost modificate.
- **Următorul pas:** verificare manuală în UI, dacă este necesară.

## Sesiunea anterioară — documentație și abstractizare

- **Data și proiect:** 21 octombrie 2026, `E:\Facultate\UBB\Sem. 3\MAP`.
- **Obiectiv autorizat:** revizuirea documentației pentru respectarea abstractizării și eliminarea contractelor repetate în implementări.
- **Modificări:** Javadoc în Laborator03 pentru domain, Repository, validatori și clasele de bază ale repository-urilor. Descrierile exprimă responsabilități și comportament observabil; validate moștenește contractul interfeței, iar regulile specifice sunt documentate la nivelul clasei. S-au păstrat @param, @return și @throws. Logica executabilă nu a fost modificată.
- **Verificări:** generare Javadoc cu JDK 21 și verificare doclint (fără avertismente pentru documentație absentă), reușită pentru domain, repository, validation, service și ui.
- **Observație:** sursele actuale diferă de istoricul din 15 octombrie: User are ID și nume, iar FriendshipId este perechea ID-urilor participanților. Documentația a fost adaptată surselor actuale.
- **Următorul pas:** revizuirea documentației de către utilizator.

## Sesiunea anterioară — comunități și UI

- **Data și proiect:** 15 octombrie 2026, `E:\Facultate\UBB\Sem. 3\MAP`.
- **Obiectiv autorizat:** verificarea implementării utilizatorului pentru comunități și legarea de UI dacă este corectă.
- **Confirmat în surse:** `Community` este imuabil, `FriendshipGraph` expune structura nemodificabilă, iar `CommunityAnalyzer` identifică componentele prin DFS și calculează cel mai lung drum simplu prin backtracking. Service-ul reconstruiește graful la cerere; `Main` injectează analyzer-ul. Implementarea a fost considerată corectă pentru interpretarea de drum simplu, cu cost potențial factorial; egalitățile pot returna oricare comunitate maximă.
- **Modificări:** `UserInterface.java` are opțiunile 7 (număr de comunități), 8 (comunitatea cea mai sociabilă), 9 (toate comunitățile). UI-ul apelează service-ul și folosește `Community.toString()` pentru afișare. Rețeaua goală este tratată prin mesajul existent din `ServiceException` sau mesaj de listă goală. Codul de domeniu/service al utilizatorului nu a necesitat corecții.
- **Verificări:** compilare JDK 21 și execuție `Main` cu CSV-uri de test în folder temporar: rețea goală cu continuarea meniului, trei componente inclusiv utilizator izolat, selecția lanțului de patru membri în locul unei stele de cinci membri, listarea comunităților, apeluri repetate și un singur utilizator izolat. Toate au trecut; datele proiectului nu au fost modificate pentru testare.
- **Următorul pas:** testare manuală prin opțiunile 7–9, verificarea/completarea JavaDoc și a contractelor repository înainte de predare. Rămâne tratarea erorilor de încărcare în `Main` și curățarea importurilor nefolosite.

## Sesiunea anterioară — cheia compusă a prieteniei

- **Data și proiect:** 15 octombrie 2026, `E:\Facultate\UBB\Sem. 3\MAP`.
- **Obiectiv autorizat:** prietenie cu ID numeric propriu, cheie compusă din ID și cele două username-uri; ștergere după ID numeric.
- **Realizat:** `FriendshipId` conține `(id, firstUsername, secondUsername)`, cu username-urile ordonate și toate cele trei câmpuri incluse în egalitate/hash. `Friendship.getId()` întoarce cheia compusă, iar `getNumericId()` întoarce ID-ul numeric. Service-ul generează ID-uri peste maximul încărcat, respinge perechile duplicate indiferent de ordine/litere mari și șterge prin `removeFriendship(Long id)`. UI-ul cere un singur ID la ștergere. Ștergerea utilizatorului elimină prieteniile pe baza username-ului.
- **CSV:** prieteniile folosesc `id,firstUsername,secondUsername`; relația existentă a fost migrată la `1,user1,user2`. Formatul utilizatorilor rămâne `id,username,firstName,lastName`.
- **Fișiere modificate:** `Friendship.java`, `FriendshipId.java`, `FriendshipValidator.java`, `FriendshipFileRepository.java`, `SocialNetworkService.java`, `UserInterface.java`, `src/data/friendships.csv` și handoff.
- **Verificări:** compilare JDK 21; teste de execuție în folder temporar pentru CSV, duplicate inversate, prietenie cu sine, ștergere după ID, ID inexistent, continuarea contorului după reîncărcare și ștergerea în cascadă cu persistență. Au trecut în afara mediului restricționat, după eșecul salvării atomice în mediul restricționat.
- **Limitări păstrate:** ID-urile sunt reconstruite din maximul rămas la repornire, deci ID-urile șterse deasupra maximului pot fi reutilizate; salvările celor două fișiere nu formează o tranzacție comună.
- **Următorul pas:** verificare manuală, apoi funcționalitățile pentru comunități; mai rămân documentarea contractelor, importuri nefolosite și tratarea erorilor de încărcare în `Main`.

## Sesiunea anterioară — username-uri

- **Data:** 15 octombrie 2026.
- **Proiect sursă:** `E:\Facultate\UBB\Sem. 3\MAP` (copia activă în această sesiune).
- **Obiectiv autorizat:** adăugare username, unicitate în service și adăugare prietenie prin username.
- **Realizat:** `User` are username final și getter; validatorul respinge username gol; service-ul elimină spațiile de la capete și verifică unicitatea fără diferență între litere mari și mici. `addUser(username, firstName, lastName)` și `addFriendship(firstUsername, secondUsername)` sunt folosite de UI. Prieteniile păstrează ID-urile intern; ștergerile folosesc în continuare ID-uri.
- **CSV:** formatul utilizatorilor este acum `id,username,firstName,lastName`. Datele existente din `src/data/users.csv` au fost migrate la `user1` pentru Tudor și `user2` pentru Stefan, cu ID-urile păstrate. Alte fișiere CSV vechi necesită migrare explicită. `Main` există și folosește `src/data/...`, relativ la directorul de lucru `Laborator03`.
- **Fișiere modificate:** `User.java`, `UserValidator.java`, `SocialNetworkService.java`, `UserInterface.java`, `UserFileRepository.java`, `src/data/users.csv` și acest handoff.
- **Verificări:** compilare JDK 21 și execuție în director temporar; au trecut verificările pentru username duplicat inclusiv majuscule/spații, username gol, ID neconsumat la respingere, căutare prin username, prietenie duplicată inversată, prietenie cu sine, username inexistent și reîncărcare CSV. Salvarea atomică a eșuat în mediul restricționat; verificarea repetată în afara lui a trecut. Datele proiectului nu au fost folosite pentru testele de execuție.
- **Următorul pas:** testare manuală din IntelliJ cu noile username-uri, apoi funcționalitățile pentru comunități. Rămân curățarea importurilor vechi din repository-uri, documentarea contractelor și tratarea erorilor de încărcare în `Main`.

## Context anterior — integrarea inițială CSV

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

- 2026-10-29 — Lab04: validatori compuși, căutări cu Predicate și meniu de filtrare, contracte Optional, factory cu Function/EnumMap, helper StreamHelper și refactorizarea colecțiilor, fișierelor și comunităților cu stream-uri; starea verificată prin citirea surselor. Compilarea și testarea întregii versiuni și documentația finală rămân de făcut. Actualizat doar handoff-ul în această etapă.
- 2026-10-03 — Document inițial creat în rădăcina MAP; starea surselor inventariată, fără modificări de cod.
- 2026-10-04 — Completarea claselor și a enumerării din `Lab02.mdj` conform codului Java, fără relații.
- 2026-10-04 — Ajustarea relațiilor adăugate de utilizator, fără legături suplimentare ale fabricii către clasele concrete.
- 2026-10-04 — Verificarea variantei finale și a PDF-ului; compilare reușită, identificarea erorii pentru coeficientul imaginar omis și a elementelor UML rămase în model.
- 2026-10-06 — Ajustarea fabricii expresiilor și documentarea extensiei prin registru; detalii păstrate în secțiunea sesiunii precedente.
- 2026-10-15 — Rețea de socializare: ID-uri automate în service, meniu UI complet pentru operațiile existente și afișare prin `toString()`. Verificări reușite înainte de adăugarea CSV; clasele de persistență CSV sunt prezente, dar integrarea și verificarea lor rămân de făcut. Actualizat handoff-ul la cererea utilizatorului.




