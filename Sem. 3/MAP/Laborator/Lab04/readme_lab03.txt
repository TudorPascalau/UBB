REȚEA DE SOCIALIZARE - LABORATORUL 4
==================================

1. Interfețe funcționale și locurile în care sunt folosite
----------------------------------------------------------
Validator<T> este @FunctionalInterface: singura metodă abstractă este validate(T).
Metoda default andThen(Validator<T> other) compune două validări în ordine.
Al doilea validator se execută numai dacă primul reușește; other null este respins.
În Main.initializeApplication, nameLengthValidator este o lambda care limitează numele și prenumele la 100 de caractere și este compusă astfel: new UserValidator().andThen(nameLengthValidator)

Predicate<User> reprezintă criteriile de căutare. 
UserCriteria.firstNameEquals și lastNameEquals sunt metode statice care întorc predicate fără a modifica utilizatorii.
Repository.findAll(Predicate<E>) este default și selectează cu filter, apoi construiește rezultatul cu collect(Collectors.toList()). 
SocialNetworkService delegă filtrarea către repository. UserInterface.filterUsers demonstrează and, or, negate și Predicate.not.

Function<Validator<E>, Repository<ID, E>> este folosit în RepositoryFactory.
Două EnumMap-uri asociază fiecărui RepositoryType funcția de creare pentru utilizatori, respectiv prietenii. 
Metodele createUserRepository și createFriendshipRepository selectează funcția și o apelează cu apply(validator).
Nu se mai folosește switch. Function este potrivit aici deoarece validatorul este furnizat la creare; nu este necesar un Supplier separat.

Comparator<User> parametriză sortarea în SocialNetworkService.getSortedUsers.


2. Cele patru tipuri de referințe la metode
-------------------------------------------
Tip                             | Exemplu                         | Loc
--------------------------------|---------------------------------|-----------------------------
Metodă statică                  | FriendshipGraph::directedEdges  | FriendshipGraph, flatMap
Instanță a unui obiect anume    | System.out::println             | UserInterface, afișare
Instanță a unui obiect oarecare | User::getLastName               | UserInterface, Comparator
Constructor                     | InMemoryRepository::new         | RepositoryFactory



3. Tabel înainte/după: bucle înlocuite
------------------------------------
Tabelul descrie prelucrările imperative anterioare și implementarea actuală.
CommunityAnalyzer era în domain în versiunea anterioară și este acum în service.

Clasă și metodă                            | Înainte                                  | După
-------------------------------------------|------------------------------------------|------------------------------------------
SocialNetworkService, constructor          | for peste utilizatori pentru ID maxim    | mapToLong(User::getId), max, orElse
SocialNetworkService.removeUser            | for și if pentru prieteniile incidente   | filter, toList, apoi forEach pentru ștergeri
SocialNetworkService, validarea            | for peste prietenii și verificarea       | validateLoadedRelationships: flatMap cu
relațiilor încărcate                       | celor doi participanți                   | Stream.of, forEach(this::ensureUserExists)
FriendshipGraph, constructor               | for pentru identificatorii utilizatorilor| map(User::getId), collect(toSet)
FriendshipGraph, constructor               | for pentru muchii în ambele direcții     | flatMap, collect(groupingBy, mapping, toSet)
FriendshipGraph, constructor               | for pentru copierea vecinilor            | collect(toMap), Set.copyOf, Map.copyOf
CommunityAnalyzer.findCommunities          | for, verificare visited și list.add      | stream, collect(ArrayList::new, ..., ArrayList::addAll)
CommunityAnalyzer, parcurgerea DFS         | while pe stivă și for peste vecini       | visitComponent recursiv, filter, forEach
CommunityAnalyzer.findMostSociableCommunity| for cu maxim și rezultat curent          | map pentru pereche comunitate/lungime,
                                           |                                          | max(Comparator.comparingInt), Optional.map

Persistența este, de asemenea, exprimată prin stream-uri:
AbstractFileRepository.loadData folosește Files.lines în try-with-resources, materializează liniile și folosește IntStream.range(...).forEach(...) pentru a păstra numărul fizic al liniei, inclusiv când există linii goale.


4. Bucle clasice păstrate și justificare
--------------------------------------
CommunityAnalyzer.longestPathFrom păstrează for-ul peste vecini pentru backtracking: adaugă nodul în drumul curent, explorează vecinii, apoi îl elimină.
Forma imperativă face vizibilă restaurarea stării și calculul maximului.

CommunityAnalyzer.longestPathLength păstrează for-ul peste punctele de pornire.
Oprește căutarea cu break când lungimea atinge community.size() - 1, limita maximă posibilă pentru un drum simplu. Astfel evită căutări suplimentare costisitoare.
Cele două bucle fac parte din algoritmul celui mai lung drum și folosesc excepția pentru backtracking permisă de cerințe.


5. Alegerea Optional în Repository
---------------------------------
Repository folosește Optional<E> consecvent pentru operațiile cu rezultat absent:
  findOne(id): entitatea găsită sau Optional.empty();
  save(entity): empty la succes, entitatea existentă dacă ID-ul este duplicat;
  update(entity): empty la succes, entitatea primită dacă ID-ul lipsește;
  delete(id): entitatea eliminată sau empty dacă ID-ul lipsește.

Optional exprimă absența în tipul de retur și evită verificările repetate de null.
Argumentele invalide și erorile de validare/persistență rămân excepții, nu empty.
Service-ul folosește orElseThrow pentru utilizatori sau prietenii inexistente.


6. Template Method versus Function pentru fișiere
------------------------------------------------
Se păstrează AbstractFileRepository și subclasele UserFileRepository și FriendshipFileRepository. 
Clasa de bază gestionează citirea, scrierea, validarea și restaurarea stării; subclasele definesc conversiile extractEntity și createEntityAsString. 
Apelul loadData are loc în constructorul subclasei după super.

Template Method reutilizează infrastructura existentă și separă clar formatele celor două entități, fără duplicarea codului de acces la fișiere. 
Alternativa cu Function<String, E> și Function<E, String> ar permite un repository generic prin compoziție și ar elimina subclasele, dar nu este necesară pentru cele două formate
actuale. Ambele variante sunt permise; este păstrată prima pentru continuitate.

