Configurare
===========
ConfigLoader citește src/main/resources/config.properties prin Properties.load(Reader), folosind BufferedReader peste FileReader, cu codificare UTF-8, într-un bloc try-with-resources.
Proprietatea repository.type acceptă valorile MEMORY, FILE sau DATABASE.
Proprietățile sunt obligatorii pentru tipul de persistență selectat, dacă lipsesc sau sunt goale, se opreste pornirea, afisand un mesaj clar.

Simple Factory
==============
RepositoryFactory este o clasa concreta, singurul loc din aplicatie care cunoaste implementarile concrete de repository. Metodele createUserRepository(validator) si createFriendshipRepository(validator) intorc Repository si folosesc switch clasic pentru acelasi RepositoryType.
ConfigLoader.load(fileName) citeste doar configuratia si intoarce Properties. Main transmite configuratia constructorului RepositoryFactory, care pastreaza o copie si valideaza tipul si proprietatile necesare persistentei selectate.
Main creeaza validatorii si transmite aceleasi instante metodelor factory-ului si serviciului. Repository-urile sunt create doar la apelarea metodelor de creare. UI primeste doar SocialNetworkService.
Clasele MemoryRepositoryFactory, FileRepositoryFactory si DbRepositoryFactory au fost eliminate.

Simple Factory centralizeaza crearea si foloseste mai putine clase. Adaugarea unui tip nou necesita extinderea RepositoryType, a switch-urilor si a validarii configuratiei, deci factory-ul nu este inchis modificarii conform OCP.
Alternativa Abstract Factory permite adaugarea unor fabrici noi fara modificarea celor existente, dar presupune mai multe clase si un mecanism de selectie a fabricii.
Structura actuala urmeaza cerinta principala a laboratorului si permite inlocuirea celor doua switch-uri cu map-uri de functii de creare la laboratorul urmator. In acest laborator nu introducem lambda-uri sau interfete functionale.

Trecerea la persistența în baza de date
=======================================
Se vor implementa operațiile din UserDbRepository și FriendshipDbRepository, inclusiv transformarea înregistrărilor din baza de date în entități, eliberarea resurselor JDBC și împachetarea erorilor de persistență în RepositoryException, cu păstrarea cauzei originale.
Implementările trebuie să respecte contractul Repository. Eventual se poate adăuga un AbstractDbRepository dacă există operații comune (ex: accesarea datei de baze).
Se configurează db.url, db.user și db.password în config.properties, apoi se setează repository.type=DATABASE.
RepositoryFactory transmite deja acești parametri și validatorii către constructorii repository-urilor pentru baza de date.
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
DIP: SocialNetworkService primeste prin constructor abstractiile Repository si Validator.
     Metodele RepositoryFactory intorc Repository. Main nu construieste repository-uri concrete.

OCP: Un tip nou de persistenta necesita modificarea RepositoryType, a switch-urilor si a validarii din RepositoryFactory.
     Service-ul si UI raman neschimbate; Simple Factory are aceasta limitare fata de OCP.

SRP: Domain reprezinta datele; validatorii definesc regulile entitatilor; repository-urile gestioneaza stocarea.
     ConfigLoader citeste configuratia; RepositoryFactory valideaza configuratia de persistenta si creeaza repository-urile.
     SocialNetworkService coordoneaza regulile retelei, CommunityAnalyzer analizeaza graful, iar UserInterface gestioneaza interactiunea.

LSP: 	Implementările funcționale MEMORY și FILE păstrează comportamentul Repository, definit prin contractul interfeței.
	La nivelul funcționalităților, nu conteaza ce fel de Repository este folosit, deoarece toate subclasele pot substitui interfața

Șabloanele de proiectare în proiect
===================================
Simple Factory:
    RepositoryFactory creeaza repository-urile pentru utilizatori si prietenii prin doua metode cu switch clasic.
    Ambele metode folosesc acelasi tip de persistenta din configuratie.

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
