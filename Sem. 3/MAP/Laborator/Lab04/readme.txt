Configurare
===========
ConfigLoader citește src/main/resources/config.properties prin Properties.load(Reader), folosind BufferedReader peste FileReader, cu codificare UTF-8, într-un bloc try-with-resources.
Proprietatea repository.type acceptă valorile MEMORY, FILE sau DATABASE.
Proprietățile sunt obligatorii pentru tipul de persistență selectat, dacă lipsesc sau sunt goale, se opreste pornirea, afisand un mesaj clar.

Abstract Factory
================
RepositoryFactory definește crearea unei familii de repository-uri pentru utilizatori și prietenii. MemoryRepositoryFactory, FileRepositoryFactory și DbRepositoryFactory creează fiecare familia corespunzătoare de persistență.
Main folosește factory-ul pentru a crea repository-urile și a asambla serviciul. Interfața cu utilizatorul primește doar SocialNetworkService.
RepositoryFactory expune createUserRepository() și createFriendshipRepository(), fără parametri. Validatorii sunt dependențe ale constructorilor FileRepositoryFactory și DbRepositoryFactory; MemoryRepositoryFactory nu primește și nu păstrează validatori.
Main creează validatorii și îi transmite către ConfigLoader.loadFactory(fileName, userValidator, friendshipValidator). ConfigLoader îi transmite doar factory-ului FILE sau DATABASE selectat. Factory-urile respective îi păstrează și îi furnizează constructorilor repository-urilor create. Aceleași instanțe de validatori sunt transmise și serviciului.
Un Simple Factory bazat pe switch ar necesita modificarea metodelor de creare pentru fiecare tip nou de persistență, ceea ce ar incalca OCP, deși ar fi fost mai simplu si ar fi constatat în mai puține clase.
Abstract Factory permite adăugarea unui factory nou fără modificarea celor existente, susținând OCP, dar presupune mai multe clase:
	Selectarea familiei este centralizată în ConfigLoader. Adăugarea unui tip de persistență necesită un factory nou, actualizarea switch-ului de configurare și o valoare nouă în RepositoryType. 
Soluția nu elimină toate modificările necesare extinderii persistenței, dar păstrează neschimbate factory-urile existente, interfața cu utilizatorul și serviciul.

Trecerea la persistența în baza de date
=======================================
Se vor implementa operațiile din UserDbRepository și FriendshipDbRepository, inclusiv transformarea înregistrărilor din baza de date în entități, eliberarea resurselor JDBC și împachetarea erorilor de persistență în RepositoryException, cu păstrarea cauzei originale.
Implementările trebuie să respecte contractul Repository. Eventual se poate adăuga un AbstractDbRepository dacă există operații comune (ex: accesarea datei de baze). 
Se configurează db.url, db.user și db.password în config.properties, apoi se setează repository.type=DATABASE.
DbRepositoryFactory transmite deja acești parametri și validatorii către constructorii repository-urilor pentru baza de date.
Main, SocialNetworkService și UserInterface nu necesită modificări pentru selectarea persistenței în baza de date. 

Politica de încărcare și validare
================================
Repository-urile pentru fișiere primesc calea și validatorul în constructor. Liniile goale sunt ignorate. Lipsa unui fișier de date înseamnă un repository gol; prima salvare reușită creează fișierul și directoarele părinte care lipsesc.
Încărcarea se oprește la prima înregistrare cu format incorect, invalidă sau cu identificator duplicat. Mesajul de eroare include numele fișierului, numărul liniei din fișier și motivul, iar excepția originală este păstrată drept cauză.
Dacă încărcarea eșuează, starea anterioară este restaurată. Am ales oprirea încărcării în locul ignorării înregistrărilor invalide pentru a evita pornirea aplicației cu o rețea de socializare incompletă sau inconsistentă.
Poziția raportată permite corectarea datelor înainte de repornire.

Justificarea împărțirii validării între serviciu și încărcarea din fișiere
=======================================================================
UserValidator și FriendshipValidator conțin regulile entităților. Service-ul le apelează înainte de salvarea entităților nou-create, indiferent de tipul de persistență. 
InMemoryRepository gestionează stocarea și verificarea argumentelor; nu apelează un validator de entități.
AbstractFileRepository apelează validatorul primit și la încărcare, deoarece înregistrările editate manual intră în aplicație fără a trece prin operațiile service-ului. 
Fiecare entitate citită este validată înainte de inserare, astfel încât datele invalide să poată fi raportate împreună cu fișierul și numărul liniei. 
Ambele căi refolosesc aceleași implementări ale validatorilor, fără duplicarea regulilor.
Regulile care implică ambele repository-uri aparțin SocialNetworkService: verificarea existenței participanților unei prietenii și ștergerea prieteniilor asociate unui utilizator șters. Un validator de entitate nu poate verifica aceste relații independent de stocare. 


Principiile SOLID în proiect
============================
DIP: 	SocialNetworkService primește prin constructor abstracțiile Repository și Validator. 
	Metodele RepositoryFactory întorc tipul Repository. 
	Main asamblează aplicația prin interfața factory-ului, iar construirea repository-urilor concrete rămâne în factory-urile concrete.

OCP: 	O familie nouă de persistență poate furniza o altă implementare RepositoryFactory fără modificarea factory-urilor existente sau a service-ului. 
	Mecanismul actual de selecție necesită totuși extinderea RepositoryType și a switch-ului din ConfigLoader.

SRP: 	User și Friendship reprezintă datele domeniului; validatorii definesc validitatea entităților; repository-urile gestionează stocarea; ConfigLoader citește configurația și selectează un factory;
	Factory-urile construiesc familii de repository-uri. SocialNetworkService coordonează regulile rețelei, CommunityAnalyzer realizează analiza grafului, iar UserInterface citește comenzile și afișează rezultatele și erorile.

LSP: 	Implementările funcționale MEMORY și FILE păstrează comportamentul Repository, definit prin contractul interfeței.
	La nivelul funcționalităților, nu conteaza ce fel de Repository este folosit, deoarece toate subclasele pot substitui interfața

Șabloanele de proiectare în proiect
===================================
Abstract Factory: 
	RepositoryFactory definește metodele de creare pentru repository-urile asociate utilizatorilor și prieteniilor. 
	MemoryRepositoryFactory, FileRepositoryFactory și DbRepositoryFactory creează fiecare o familie coerentă de persistență.

Template Method: 
	AbstractFileRepository definește pașii comuni de încărcare, validare și stocare în loadData și pașii comuni de conversie în text și scriere în writeToFile. 
	Aceste metode apelează extractEntity și createEntityAsString, implementate în UserFileRepository și FriendshipFileRepository. 
	Subclasele apelează loadData după încheierea constructorului superclasei. 

Strategy: 
	Validator<T> definește operația de validare. UserValidator și FriendshipValidator furnizează regulile pentru tipurile lor de entități.
	Comportamentul de validare poate fi astfel furnizat fără ca repository și service să depindă de clasele concrete ale validatorilor.

Decorator: 
	Operațiile de intrare/ieșire pe caractere folosesc compunerea cititoarelor și scriitoarelor cu buffer din biblioteca standard. (BufferedReader / BufferedWriter)

Tratarea excepțiilor
====================
ValidationException, RepositoryException și ServiceException sunt excepții unchecked. 
ApplicationInitializationException este o excepție unchecked pentru eșecurile de pornire a aplicației. 
Main.initializeApplication() împachetează IOException, RepositoryException, ValidationException, ServiceException, IllegalArgumentException și UnsupportedOperationException apărute la inițializare, păstrând cauza originală.
Main.main() tratează doar ApplicationInitializationException pentru pornire și afișează mesajul. ui.run() este apelat după încheierea inițializării, astfel încât erorile operațiilor din timpul utilizării nu sunt transformate în erori de pornire.
