Rețea de socializare — Laboratorul 3
==================================

Configurare și pornire
=====================
Proiectul Gradle / IntelliJ se află în folderul SocialNetwork. Aplicația se pornește prin clasa Main, cu directorul de lucru setat la SocialNetwork, deoarece căile sunt relative la acest director.
ConfigLoader citește src/main/resources/config.properties prin Properties.load(Reader), folosind BufferedReader peste FileReader, cu codificare UTF-8, într-un bloc try-with-resources.
repository.type acceptă valorile MEMORY, FILE sau DATABASE. RepositoryFactory verifică tipul și proprietățile necesare doar pentru persistența selectată. O proprietate obligatorie lipsă sau goală ori un tip necunoscut oprește pornirea cu un mesaj clar.
Pentru FILE sunt necesare repository.users.file și repository.friendships.file. Pentru DATABASE sunt necesare db.url, db.user și db.password. Parametrii sunt citiți din configurare, nu sunt scriși în codul Java.

Formatul datelor
===============
Configurația actuală folosește data/users.csv și data/friendships.csv. În ciuda extensiei .csv, separatorul este punct și virgulă, conform formatului de înregistrare cerut de laborator. Numele fișierelor diferă de data/utilizatori.txt și data/prietenii.txt indicate în PDF; schimbarea lor presupune redenumirea fișierelor și actualizarea configurării.
Fiecare linie nevidă reprezintă o entitate:
- utilizator: id;firstName;lastName
- prietenie: firstUserId;secondUserId;friendsSince
Data prieteniei folosește formatul ISO_LOCAL_DATE_TIME, de exemplu 2026-10-19T10:30. Citirea și scrierea datelor folosesc UTF-8 și căi relative.
FriendshipId normalizează perechea de identificatori, cu identificatorul mai mic primul: prieteniile (1, 2) și (2, 1) au aceeași identitate. Entity și FriendshipId definesc equals și hashCode consecvent și tratează comparațiile cu null și cu obiecte de alt tip.

Simple Factory și configurarea persistenței
==========================================
RepositoryFactory este clasa concretă care centralizează cunoașterea implementărilor concrete de repository la asamblarea aplicației. Metodele createUserRepository(validator) și createFriendshipRepository(validator) întorc Repository<Long, User>, respectiv Repository<FriendshipId, Friendship>, și folosesc switch clasic pentru același RepositoryType.
ConfigLoader citește doar configurarea și întoarce Properties. Main transmite proprietățile constructorului RepositoryFactory, care păstrează o copie și validează configurația fără a deschide fișierele de date sau conexiuni la baza de date. Repository-urile sunt create la apelarea metodelor de creare.
Main creează validatorii și îi transmite factory-ului. SocialNetworkService primește cele două repository-uri și CommunityAnalyzer, fără validatori. UserInterface primește serviciul. Main, service-ul și UI-ul nu construiesc repository-uri concrete.
Nu se folosește Singleton: factory-ul este instanțiat o dată la pornire.

Simple Factory folosește puține clase, dar adăugarea unui tip de persistență necesită extinderea RepositoryType, a switch-urilor și a validării configurării. Factory-ul nu este astfel închis modificării conform OCP.
Alternativa Abstract Factory permite adăugarea unor implementări noi de fabrică fără modificarea celor existente, dar introduce mai multe clase și necesită în continuare un mecanism de selecție a fabricii.
Soluția actuală urmează cerința de Simple Factory și switch clasic a acestui laborator. Nu introduce expresii lambda, referințe la metode sau Stream API.

Trecerea la persistența în baza de date
=====================================
UserDbRepository și FriendshipDbRepository implementează Repository și primesc validatorul și parametrii conexiunii prin constructor. În acest laborator sunt doar schelete: operațiile aruncă UnsupportedOperationException și nu deschid conexiuni JDBC. Factory-ul le creează deja pentru repository.type=DATABASE; prima citire din timpul inițializării produce un mesaj controlat că persistența DATABASE nu este implementată.
Pentru implementarea ulterioară se completează operațiile acestor clase, inclusiv conversia înregistrărilor în entități, validarea, eliberarea resurselor JDBC și împachetarea erorilor în RepositoryException, cu păstrarea cauzei originale. Se pot extrage operațiile comune într-o clasă de bază dacă este necesar.
Se configurează db.url, db.user și db.password și se selectează repository.type=DATABASE. Main, SocialNetworkService și UserInterface nu necesită modificări pentru selectarea noii persistențe. Implementările trebuie să respecte contractul Repository.

Politica de încărcare și validare
================================
AbstractFileRepository<ID, E extends Entity<ID>> extinde InMemoryRepository<ID, E>. Subclasele primesc calea și validatorul și apelează loadData după încheierea constructorului superclasei. Astfel, constructorul superclasei nu apelează metode suprascrise care ar putea folosi câmpuri neinițializate ale subclasei.
Citirea și scrierea sunt comune, prin Files.newBufferedReader și Files.newBufferedWriter, în blocuri try-with-resources. Subclasele UserFileRepository și FriendshipFileRepository implementează conversiile extractEntity și createEntityAsString. split(";", -1) păstrează câmpurile goale de la finalul înregistrării.
Liniile goale sunt ignorate. Un fișier de date inexistent înseamnă un repository gol la pornire; prima salvare reușită creează fișierul și directoarele părinte necesare. Un fișier de configurare lipsă este, în schimb, o eroare de pornire.
Încărcarea se oprește la prima înregistrare cu format incorect, invalidă sau cu identificator duplicat. Mesajul include fișierul, numărul fizic al liniei și motivul, iar excepția originală este păstrată drept cauză. Starea anterioară încărcării este restaurată.
Alegerea opririi încărcării evită pornirea cu date incomplete sau inconsistente; poziția raportată permite corectarea înregistrării înainte de repornire.

Validarea entităților aparține repository-ului. InMemoryRepository primește Validator<E> și îl apelează înainte de save și update. AbstractFileRepository refolosește această validare prin super.save la încărcare, fără a rescrie fișierul citit. Regulile rămân în UserValidator și FriendshipValidator; repository-ul doar le invocă.
Această alegere aplică aceeași politică atât entităților introduse prin aplicație, cât și datelor editate manual în fișiere, fără duplicarea regulilor.
SocialNetworkService verifică regulile care implică rețeaua: participanții unei prietenii trebuie să existe, iar ștergerea unui utilizator elimină și prieteniile asociate. La pornire verifică și referințele prieteniilor încărcate. Service-ul nu repetă validarea entităților și nu depinde de clasele concrete ale validatorilor.
Mutarea validării entităților în repository este o refactorizare arhitecturală distinctă de adăugarea persistenței în fișier.

Salvare și recuperare după erori
===============================
După fiecare save, update sau delete care modifică starea, AbstractFileRepository scrie întregul conținut într-un fișier temporar și înlocuiește atomic fișierul destinație. Operațiile fără modificări nu rescriu fișierul.
Dacă scrierea eșuează, starea anterioară din memorie este restaurată și eroarea este propagată ca RepositoryException. Dacă și ștergerea fișierului temporar eșuează, eroarea de curățare este păstrată ca excepție suprimată pe cauza I/O inițială.
La ștergerea utilizatorului, service-ul șterge mai întâi prieteniile incidente, apoi utilizatorul. La un eșec de persistență încearcă restaurarea prieteniilor deja eliminate. O recuperare incompletă este raportată explicit, cu păstrarea erorii inițiale și a erorilor de recuperare.
Înlocuirea atomică se aplică separat fiecărui fișier; cele două fișiere nu formează o tranzacție comună. Recuperarea este o încercare de restaurare, nu o garanție în cazul unor noi erori I/O sau al întreruperii procesului.

Principiile SOLID în proiect
===========================
DIP: SocialNetworkService depinde de abstracțiile Repository, primite prin constructor. Repository-urile depind de Validator<E>, iar factory-ul întoarce tipurile abstracte Repository. Main nu construiește repository-uri concrete.
OCP: Service-ul și UI-ul rămân neschimbate la alegerea persistenței. Simple Factory are limita descrisă anterior: un tip nou necesită modificarea enum-ului, a switch-urilor și a validării configurării.
SRP: Domain reprezintă datele; validatorii definesc regulile entităților; repository-urile gestionează stocarea. ConfigLoader citește configurația, RepositoryFactory validează configurația de persistență și creează repository-urile, SocialNetworkService coordonează regulile rețelei, CommunityAnalyzer analizează graful, iar UserInterface gestionează interacțiunea.
LSP: Implementările funcționale MEMORY și FILE respectă contractul Repository: aceleași convenții pentru rezultate, duplicate, entități absente și argumente invalide. De exemplu, delete(null) aruncă IllegalArgumentException. FILE adaugă persistența și erorile documentate de stocare. Scheletele DATABASE nu sunt încă substituenți funcționali și aruncă intenționat UnsupportedOperationException conform cerinței laboratorului.

Șabloanele de proiectare în proiect
==================================
Simple Factory: RepositoryFactory creează repository-urile pentru utilizatori și prietenii prin două metode cu switch clasic, folosind același tip de persistență configurat.
Template Method: AbstractFileRepository definește pașii comuni pentru încărcare și scriere și apelează extractEntity și createEntityAsString, implementate în subclase. Codul de citire și scriere nu se duplică în repository-urile concrete.
Strategy: Validator<T> definește contractul validării. UserValidator și FriendshipValidator furnizează regulile specifice și sunt injectate în repository-uri, care depind de interfață.
Decorator: ConfigLoader folosește BufferedReader peste FileReader, adăugând citirea cu buffer unui Reader. Persistența datelor utilizează cititoare și scriitoare cu buffer furnizate de NIO.2.

Tratarea excepțiilor și contracte
================================
ValidationException, RepositoryException, ServiceException, UIException și ApplicationInitializationException sunt excepții unchecked. RepositoryException are constructor (String, Throwable) pentru păstrarea cauzei originale. La încărcare sunt păstrate inclusiv IOException, NumberFormatException, DateTimeParseException și ValidationException.
Blocurile catch din repository și service fac traducerea excepțiilor sau recuperarea stării; nu afișează mesaje utilizatorului. Nu se folosesc catch-uri goale, catch(Exception), catch(Throwable) sau printStackTrace ca singură tratare.
Main.initializeApplication împachetează erorile așteptate de inițializare în ApplicationInitializationException, păstrând cauza. Main.main afișează mesajul și oprește pornirea controlat. ui.run este apelat după inițializarea reușită, astfel încât erorile din timpul folosirii aplicației nu sunt transformate în erori de pornire.
UI raportează intrările numerice invalide, argumentele incorecte, erorile de validare, operațiile de rețea invalide și erorile de persistență, apoi continuă meniul. Închiderea intrării în timpul unei operații este raportată și încheie interfața controlat.
Javadoc-ul este în engleză și documentează parametrii, rezultatele și excepțiile unchecked. Metodele suprascrise moștenesc contractele interfeței sau superclasei, iar constructorii documentează propriile erori. Excepțiile unchecked sunt descrise prin @throws, fără clauze throws în antet.

Demonstrație și livrabile
========================
La predare se demonstrează adăugarea și ștergerea utilizatorilor și prieteniilor, persistența după repornire, numărul de comunități și comunitatea cea mai sociabilă, fișierul lipsă, raportarea unei linii corupte și selecția MEMORY / DATABASE din configurare.
Pentru demonstrarea erorilor se folosesc copii de test ale datelor și căi relative în configurare, pentru a păstra datele principale.
Se predau sursele proiectului Gradle / IntelliJ, config.properties, folderul data/, un fișier separat de test cu linii corupte și acest readme. Fișierul separat cu linii corupte nu există încă în proiectul verificat și trebuie adăugat înainte de predare.
Laboratorul trebuie încărcat în assignment-ul de pe Teams pentru a fi considerat predat.
