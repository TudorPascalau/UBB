Configurare
===========
ConfigLoader citeste configuratia prin Properties.load(Reader), folosind FileReader pentru
src/main/resources/config.properties. Nu sunt folosite InputStream sau Stream API.
repository.type accepta MEMORY, FILE sau DATABASE. Proprietatile lipsa sau goale
necesare modului selectat si tipurile necunoscute opresc pornirea cu un mesaj clar.
Caile fisierelor sunt relative la directorul de lucru; porniti din SocialNetwork.
DATABASE creeaza doar repository-uri schelet, fara conexiune JDBC. La prima citire,
aplicatia raporteaza ca persistenta DATABASE nu este inca implementata.

Abstract Factory si OCP
======================
RepositoryFactory defineste crearea unei familii de repository-uri: utilizatori
si prietenii. MemoryRepositoryFactory, FileRepositoryFactory si DbRepositoryFactory
implementeaza fiecare familia corespunzatoare. Main foloseste fabrica pentru a crea
repository-urile si construieste serviciul. UI-ul primeste doar SocialNetworkService.
Metodele fabricii primesc validatorul ca parametru. Main creeaza validatorii si
transmite aceleasi instante repository-urilor si serviciului. ConfigLoader
gestioneaza configuratia persistentei, fara sa creeze validatori.
Clasele DB implementeaza direct Repository; toate operatiile lor arunca
UnsupportedOperationException, fara o clasa de baza comuna.

Un Simple Factory cu switch ar necesita modificarea metodelor de creare la fiecare
tip nou de persistenta. Avantajele sale sunt simplitatea si numarul redus de clase.
Abstract Factory permite adaugarea unei fabrici noi fara modificarea fabricilor
existente, respectand mai bine OCP, dar necesita mai multe clase.

Selectia familiei este centralizata in ConfigLoader. Main cere fabrica, asambleaza
dependentele aplicatiei si transmite serviciul constructorului UserInterface.
In ConfigLoader exista un switch
de configurare; adaugarea unui backend cere actualizarea acestui punct si a enum-ului
RepositoryType. Solutia nu elimina toate modificarile la extindere, dar pastreaza
neschimbate fabricile existente, UI-ul si serviciul.
Nu folosim Singleton: instanta fabricii este creata o singura data la pornire.

Validarea la incarcare
=====================
Repository-urile de fisier primesc calea si validatorul in constructor. O linie
invalida opreste incarcarea; mesajul include fisierul, numarul liniei si cauza.
Liniile goale sunt ignorate. Un fisier lipsa reprezinta un repository gol;
prima salvare creeaza fisierul. Serviciul verifica si referintele dintre entitati.
