Laborator03 - refactorizare pe baza cursului 3

RULARE
JDK 21. Rulati Main din IntelliJ, cu directorul de lucru setat la radacina
proiectului Laborator03. Nu sunt necesare biblioteci externe sau configurari.

DATE
UserFileRepository foloseste data/users.csv: id;prenume;nume.
FriendshipFileRepository foloseste data/friendships.csv:
idUtilizator1;idUtilizator2;dataPrieteniei.
Caile sunt relative la radacina proiectului. Codificare UTF-8.
FriendshipId este perechea imutabila normalizata (minID,maxID).
Data prieteniei este LocalDateTime in format ISO.
Datele au fost migrate din CSV-urile vechi. Acestea nu contineau data prieteniei;
2026-10-19T00:00 este o valoare explicita de migrare, nu o data istorica cunoscuta.
Pentru prieteniile noi se foloseste ora locala a aplicatiei, la minut.

ARHITECTURA
AbstractFileRepository extinde InMemoryRepository. Subclasele implementeaza
extractEntity si createEntityAsString, folosind Template Method.
Se folosesc NIO.2, BufferedReader/BufferedWriter si try-with-resources.
Incarcarea apeleaza super.save, pentru a nu rescrie fisierul in timpul citirii.
Conversiile nu sunt apelate din constructorul clasei de baza.
Validatorii sunt injectati prin constructor (Strategy). Service-ul depinde de
Repository si Validator. UI construieste repository-urile de fisier la pornire.
Factory-ul, configurarea backend-urilor si repository-urile DB sunt amanate.

VALIDARE SI ERORI
Validatorii sunt apelati exclusiv in service, la adaugare si la initializarea
service-ului, dupa incarcarea ambelor repository-uri. Sunt verificati intai
utilizatorii, apoi prieteniile, inainte de calcularea urmatorului ID.
FriendshipValidator verifica doar campurile; service-ul verifica existenta
ambilor participanti. Numele trebuie sa contina doar litere, inclusiv diacritice.
Repository.save/update nu valideaza semantic entitatile. Orice viitoare
operatie de actualizare din service trebuie sa valideze inainte de update.
Un fisier lipsa inseamna repository gol si este creat la prima salvare.
O eroare de format sau un ID duplicat opreste incarcarea cu numarul liniei,
calea si motivul. Datele interpretabile, dar semantic invalide sunt respinse
ulterior de service, fara numarul liniei. UI afiseaza eroarea de pornire si
nu deschide meniul. Verificarea initiala nu rescrie fisierele.
Aceasta alegere evita suprascrierea unui fisier corupt cu un subset de date.
RepositoryException pastreaza cauza originala prin constructor.
Catch-urile din repository/service traduc erori sau incearca recuperarea;
mesajele pentru utilizator sunt afisate in UI.
Nu se folosesc lambda, method references, stream-uri sau serializare binara.

PERSISTENTA
Fiecare modificare reusita rescrie fisierul printr-un temporar si mutare atomica.
Daca scrierea esueaza, memoria este restaurata. Sistemul de fisiere trebuie sa
suporte ATOMIC_MOVE; altfel operatia raporteaza explicit eroarea.
Stergerea unui utilizator elimina prieteniile lui; la esec se incearca recuperarea.
Cele doua fisiere nu formeaza o tranzactie atomica comuna: o intrerupere brusca
intre scrieri sau un esec al recuperarii poate necesita verificarea lor manuala.
