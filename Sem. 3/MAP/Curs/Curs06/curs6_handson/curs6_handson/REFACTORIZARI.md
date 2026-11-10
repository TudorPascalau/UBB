# curs6_handson: Persistența în baza de date (JDBC + PostgreSQL)

Pornește de la `curs5_handson` (cerințele 1–13) și adaugă repository-ul în baza de date.

**Pregătire:** în pgAdmin creați baza `socialnetwork`, apoi rulați `sql/retea.sql` în Query Tool (tabelele `users` și `friendships`, 6 utilizatori, 5 prietenii). Scriptul nu șterge date existente.

## Ce s-a schimbat față de curs5

| Fișier | Modificare |
|---|---|
| `build.gradle.kts` | dependența `org.postgresql:postgresql` (driverul JDBC) |
| `config.properties` | `repository.type=DATABASE` |
| `sql/retea.sql` (nou) | scriptul bazei de date |
| `SqlFunction` (nou) | interfață funcțională care poate arunca `SQLException` (`Function` nu poate) |
| `RepositoryException` (nou) | excepție unchecked care împachetează `SQLException` (ca `UncheckedIOException` la fișiere) |
| `UtilizatorDbRepository` | implementat cu JDBC simplu: fiecare metodă își deschide conexiunea în try-with-resources (varianta abstractă, cu `executa` + `SqlFunction`, este în `curs6/UtilizatorDbRepository_preaabstract.java`) |
| `RepositoryFactory`, `Repository` | **nemodificate**: `stream()` și `findAll(Predicate)` merg și pe baza de date |
| `Main` | rescris: doar cerințele cursului 6 (1–7), fiecare cu enunțul în comentariu și soluția; cerințele 2–6 sunt implementate în `UtilizatorDbRepository` |
| `db_handson` (nou) | exercițiile de la curs: Ex1–Ex5 |

---

## curs5_handson: Interfețe funcționale și Java 8

Pornește de la `curs3_handson` (cerințele 1–4) și adaugă:

- **Cerințele 7–10**, aceleași ca la seminarul 5 (cod identic cu `sem5-InterfeteFunctionale`, adaptat la Optional).
- **Cerințele 11–13**, partea de Java 8 pe care seminarul o lasă pentru curs: Optional, Stream API, NIO.

### Ce s-a schimbat față de curs3

| Fișier | Refactorizare |
|---|---|
| `Validator` | `@FunctionalInterface`, metoda default `andThen` (sem5), metoda statică `of(Predicate, mesaj)` (curs) |
| `Repository` | `findOne/save/delete/update` întorc `Optional<E>` în loc de `null`; metode default `stream()` și `findAll(Predicate)` (implementată cu stream) |
| `InMemoryRepository` | `Optional.ofNullable / of / empty`; Javadoc adăugat. Bug-ul `delete(null)` rămâne intenționat |
| `AbstractFileRepository` | **șters**, înlocuit de `FileRepository` |
| `FileRepository` (nou) | compoziție în loc de Template Method: primește `Function<String,E>` și `Function<E,String>`; citire cu `Files.lines`, scriere cu `Files.write` |
| `UtilizatorFileRepository` | nu mai suprascrie metode abstracte; transmite `::dinLinie`, `::catreLinie` lui `super`. Constructorul are aceeași semnătură |
| `UtilizatorDbRepository` | semnături cu `Optional` (se implementează în cursul 6) |
| `RepositoryFactory` | `Map<RepositoryType, Supplier<...>>` în loc de `switch` (sem5) |
| `CriteriiUtilizator`, `util/Colectii` | noi (sem5); `Colectii` cu stream-uri, `reduce` întoarce `Optional` |
| `Main` | `salveaza` cu `ifPresentOrElse`; `reteaDemo` cu `orElseThrow`; cerințele 7–13 |
| `ex/G11`, `ex/functional/*` | exemplele de la seminarul 5 (încălzire, Completați tipul) |
