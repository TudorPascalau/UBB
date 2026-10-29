Rețea de socializare — Laboratorul 4
====================================

Interfețe funcționale și compunerea validatorilor
================================================
Validator<T> este adnotată cu @FunctionalInterface și păstrează o singură metodă abstractă: validate(T).
Metoda default andThen(Validator<T> other) întoarce un validator nou, exprimat ca lambda, care execută validatorul curent și apoi validatorul primit. Dacă primul aruncă o excepție, al doilea nu se execută. Un validator other null este respins imediat cu IllegalArgumentException.
În Main, Validator<User> nameLengthValidator este o regulă lambda care limitează numele și prenumele la câte 100 de caractere. Această limită este o alegere demonstrativă pentru regula nouă, nu o valoare impusă de enunț.
Regula se compune prin new UserValidator().andThen(nameLengthValidator), fără modificarea clasei UserValidator și fără clase noi. Validatorul existent verifică mai întâi entitatea și numele nenule, astfel încât regula suplimentară poate apela length() în siguranță în această compunere.
Repository-ul primește validatorul compus prin interfața Validator<User>; regula suplimentară se aplică atât la save/update, cât și la încărcarea datelor din fișier. Datele care depășesc limita nouă sunt respinse; celelalte reguli și formatul fișierelor rămân cele existente.
Secțiunile de mai jos descriu baza de la laboratorul 3 și vor fi actualizate pe măsura refactorizării.

Configurare și pornire
======================
ConfigLoader citește src/main/resources/config.properties prin Properties.load(Reader), într-un bloc try-with-resources. 
RepositoryFactory verifică tipul și proprietățile necesare doar pentru persistența selectată. O proprietate obligatorie lipsă sau goală ori un tip necunoscut oprește pornirea cu un mesaj clar. Pentru FILE sunt necesare repository.users.file și repository.friendships.file. 
Pentru DATABASE sunt necesare db.url, db.user și db.password. Parametrii sunt citiți din configurare, nu sunt scriși în codul Java.

Simple Factory și configurarea persistenței
===========================================
RepositoryFactory este clasa concretă care centralizează cunoașterea implementărilor concrete de repository la asamblarea aplicației. 
Repository-urile sunt create la apelarea metodelor de creare.
Simple Factory folosește puține clase, dar adăugarea unui tip de persistență necesită extinderea RepositoryType, a switch-urilor și a validării configurării. Factory-ul nu este astfel închis modificării conform OCP.
Alternativa Abstract Factory permite adăugarea unor implementări noi de fabrică fără modificarea celor existente, dar introduce mai multe clase și necesită în continuare un mecanism de selecție a fabricii, care nu ar fi nici el complet închis, deci acceptăm acest compromis.

Trecerea la persistența în baza de date
=======================================
UserDbRepository și FriendshipDbRepository implementează Repository și primesc validatorul și parametrii conexiunii prin constructor. În acest laborator sunt doar schelete: operațiile aruncă UnsupportedOperationException. 
Factory-ul le creează deja pentru repository.type=DATABASE; prima citire din timpul inițializării produce un mesaj controlat că persistența DATABASE nu este implementată.
Pentru implementarea ulterioară se completează operațiile acestor clase, inclusiv conversia înregistrărilor în entități, validarea, eliberarea resurselor JDBC și împachetarea erorilor în RepositoryException, cu păstrarea cauzei originale. Se pot extrage operațiile comune într-o clasă de bază dacă este necesar.

Politica de încărcare și validare
=================================
AbstractFileRepository<ID, E extends Entity<ID>> extinde InMemoryRepository<ID, E>. Subclasele primesc calea și validatorul și apelează loadData după încheierea constructorului superclasei. Astfel, constructorul superclasei nu apelează metode suprascrise care ar putea folosi câmpuri neinițializate ale subclasei.
Liniile goale sunt ignorate. Un fișier de date inexistent înseamnă un repository gol la pornire; prima salvare reușită creează fișierul și directoarele părinte necesare. 
Un fișier de configurare lipsă este, în schimb, o eroare de pornire.
Încărcarea se oprește la prima înregistrare cu format incorect, invalidă sau cu identificator duplicat. Mesajul include fișierul, numărul fizic al liniei și motivul, iar excepția originală este păstrată drept cauză. Starea anterioară încărcării este restaurată.
Alegerea opririi încărcării evită pornirea cu date incomplete sau inconsistente; poziția raportată permite corectarea înregistrării înainte de repornire.

Validarea entităților aparține repository-ului. InMemoryRepository primește Validator<E> și îl apelează înainte de save și update. AbstractFileRepository refolosește această validare prin super.save la încărcare, fără a rescrie fișierul citit. Regulile rămân în UserValidator și FriendshipValidator; repository-ul doar le invocă.
Această alegere aplică aceeași politică atât entităților introduse prin aplicație, cât și datelor editate manual în fișiere, fără duplicarea regulilor.
SocialNetworkService verifică regulile care implică rețeaua: participanții unei prietenii trebuie să existe, iar ștergerea unui utilizator elimină și prieteniile asociate. La pornire verifică și referințele prieteniilor încărcate. Service-ul nu repetă validarea entităților și nu depinde de clasele concrete ale validatorilor.

Principiile SOLID în proiect
============================
DIP: SocialNetworkService depinde de abstracțiile Repository, primite prin constructor. Repository-urile depind de Validator<E>, iar factory-ul întoarce tipurile abstracte Repository. Main nu construiește repository-uri concrete.
OCP: Service-ul și UI-ul rămân neschimbate la alegerea persistenței. Simple Factory are limita descrisă anterior: un tip nou necesită modificarea enum-ului, a switch-urilor și a validării configurării.
SRP: Domain reprezintă datele; validatorii definesc regulile entităților; repository-urile gestionează stocarea. ConfigLoader citește configurația, RepositoryFactory validează configurația de persistență și creează repository-urile, SocialNetworkService coordonează regulile rețelei, CommunityAnalyzer analizează graful, iar UserInterface gestionează interacțiunea.
LSP: Implementările funcționale MEMORY și FILE respectă contractul Repository: aceleași convenții pentru rezultate, duplicate, entități absente și argumente invalide. De exemplu, delete(null) aruncă IllegalArgumentException. FILE adaugă persistența și erorile documentate de stocare. Scheletele DATABASE nu sunt încă substituenți funcționali și aruncă intenționat UnsupportedOperationException conform cerinței laboratorului.

Șabloanele de proiectare în proiect
===================================
Simple Factory: RepositoryFactory creează repository-urile pentru utilizatori și prietenii prin două metode cu switch clasic, folosind același tip de persistență configurat.
Template Method: AbstractFileRepository definește pașii comuni pentru încărcare și scriere și apelează extractEntity și createEntityAsString, implementate în subclase. Codul de citire și scriere nu se duplică în repository-urile concrete.
Strategy: Validator<T> definește contractul validării. UserValidator și FriendshipValidator furnizează regulile specifice și sunt injectate în repository-uri, care depind de interfață.
Decorator: ConfigLoader folosește BufferedReader peste FileReader, adăugând citirea cu buffer unui Reader. Persistența datelor utilizează cititoare și scriitoare cu buffer furnizate de NIO.2.

Tratarea excepțiilor și contracte
=================================
ValidationException, RepositoryException, ServiceException, UIException și ApplicationInitializationException sunt excepții unchecked. RepositoryException are constructor (String, Throwable) pentru păstrarea cauzei originale. La încărcare sunt păstrate inclusiv IOException, NumberFormatException, DateTimeParseException și ValidationException.s
Main.initializeApplication împachetează erorile așteptate de inițializare în ApplicationInitializationException, păstrând cauza. Main.main afișează mesajul și oprește pornirea controlat. ui.run este apelat după inițializarea reușită, astfel încât erorile din timpul folosirii aplicației nu sunt transformate în erori de pornire.
UI raportează intrările numerice invalide, argumentele incorecte, erorile de validare, operațiile de rețea invalide și erorile de persistență, apoi continuă meniul. Închiderea intrării în timpul unei operații este raportată și încheie interfața controlat.
