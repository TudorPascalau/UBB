// Varianta abstracta (executa + SqlFunction), pastrata ca referinta; factory-ul foloseste UtilizatorDbRepository.
package curs.repository.db;

import curs.domain.Utilizator;
import curs.domain.validators.Validator;
import curs.repository.Repository;
import curs.repository.RepositoryException;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

/**
 * Database repository for users; every operation is a query on the
 * table users(id, first_name, last_name). Keeps nothing in memory.
 * The friends of a user are not loaded.
 */
public class UtilizatorDbRepository_refactored implements Repository<Long, Utilizator> {

    private static final String SELECT_ALL = "SELECT id, first_name, last_name FROM users ORDER BY id";
    private static final String SELECT_ONE = "SELECT id, first_name, last_name FROM users WHERE id = ?";
    private static final String INSERT = "INSERT INTO users (id, first_name, last_name) VALUES (?, ?, ?) ON CONFLICT (id) DO NOTHING";
    private static final String UPDATE = "UPDATE users SET first_name = ?, last_name = ? WHERE id = ?";
    private static final String DELETE = "DELETE FROM users WHERE id = ?";

    private final Validator<Utilizator> validator;
    private final String url;
    private final String user;
    private final String password;

    /**
     *
     * @param validator - the validation strategy for users
     * @param url       - the JDBC url of the database
     * @param user      - the database user
     * @param password  - the password of the database user
     */
    public UtilizatorDbRepository_refactored(Validator<Utilizator> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    // ---------------- Cerinta 2. Un rand din tabela -> un Utilizator ----------------
    // Scrieti metoda dinRand(ResultSet rs), care construieste un Utilizator din randul curent
    // (coloanele id, first_name, last_name).

    /**
     *
     * @param rs - a ResultSet positioned on a row of the table users
     * @return the user described by the current row
     * @throws SQLException if a column does not exist
     */
    private static Utilizator dinRand(ResultSet rs) throws SQLException {
        Utilizator u = new Utilizator(rs.getString("first_name"), rs.getString("last_name"));
        u.setId(rs.getLong("id"));
        return u;
    }

    // ---------------- Cerinta 3. findAll cu JDBC ----------------
    // Implementati findAll: toti utilizatorii, ordonati dupa id.
    //   - Connection, PreparedStatement si ResultSet se deschid in try-with-resources;
    //   - ResultSet-ul se parcurge cu while (rs.next());
    //   - SQLException (checked) se transforma in RepositoryException (unchecked).
    // Solutia (prima varianta, inlocuita la Cerinta 4):
    //
    //    public Iterable<Utilizator> findAll() {
    //        List<Utilizator> rezultat = new ArrayList<>();
    //        try (Connection c = DriverManager.getConnection(url, user, password);
    //             PreparedStatement ps = c.prepareStatement(SELECT_ALL);
    //             ResultSet rs = ps.executeQuery()) {
    //            while (rs.next())
    //                rezultat.add(dinRand(rs));
    //        } catch (SQLException e) {
    //            throw new RepositoryException("Eroare la baza de date: " + e.getMessage(), e);
    //        }
    //        return rezultat;
    //    }

    // ---------------- Cerinta 4. Codul comun scris o singura data ----------------
    // Fiecare operatie ar repeta: deschide conexiunea, pregateste instructiunea, trateaza SQLException.
    // Scrieti metoda executa(sql, actiune, params...): ea face partea comuna, iar actiunea
    // (ce difera) o primeste ca lambda de tip SqlFunction<PreparedStatement, R>.
    // Rescrieti findAll cu executa.
    // Intrebare: de ce nu putem folosi Function<PreparedStatement, R>?

    /**
     * opens a connection, prepares the statement, sets the parameters (?, in order)
     * and applies the action; the connection and the statement are always closed
     *
     * @param sql     - the SQL statement, with ? for parameters
     * @param actiune - what is done with the prepared statement (query or update)
     * @param params  - the values of the parameters, in the order of the ?
     * @param <R>     - type of the result
     * @return the result of the action
     * @throws RepositoryException if a database access error occurs
     */
    private <R> R executa(String sql, SqlFunction<PreparedStatement, R> actiune, Object... params) {
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            for (int i = 0; i < params.length; i++)
                ps.setObject(i + 1, params[i]);      // parametrii se numara de la 1
            return actiune.apply(ps);
        } catch (SQLException e) {
            throw new RepositoryException("Eroare la baza de date: " + e.getMessage(), e);
        }
    }

    /**
     * runs a query and converts every row into a user
     *
     * @param ps - the prepared statement, with the parameters already set
     * @return the users returned by the query (an empty list - if there is no row)
     * @throws SQLException if a database access error occurs
     */
    private static List<Utilizator> citeste(PreparedStatement ps) throws SQLException {
        List<Utilizator> rezultat = new ArrayList<>();
        try (ResultSet rs = ps.executeQuery()) {
            while (rs.next())
                rezultat.add(dinRand(rs));
        }
        return rezultat;
    }

    /**
     *
     * @return all users, ordered by id
     * @throws RepositoryException if a database access error occurs
     */
    @Override
    public Iterable<Utilizator> findAll() {
        return executa(SELECT_ALL, UtilizatorDbRepository_refactored::citeste);   // referinta la metoda statica
    }

    // ---------------- Cerinta 5. findOne cu parametru ----------------
    // Implementati findOne(id) cu executa: SELECT cu WHERE id = ? (nu concatenam id-ul in SQL).
    // Rezultatul este Optional: primul element din lista citita, daca exista.

    /**
     *
     * @param id - the id of the user to be returned; must not be null
     * @return an Optional with the user with the specified id
     * or Optional.empty() - if there is no user with the given id
     * @throws IllegalArgumentException if id is null.
     * @throws RepositoryException      if a database access error occurs
     */
    @Override
    public Optional<Utilizator> findOne(Long id) {
        if (id == null)
            throw new IllegalArgumentException("id must be not null");
        return executa(SELECT_ONE, ps -> citeste(ps).stream().findFirst(), id);
    }

    // ---------------- Cerinta 6. save ----------------
    // Implementati save: validare, apoi INSERT.
    // Daca id-ul exista deja, intoarceti Optional.of(entity), ca la InMemoryRepository.
    // Indiciu: ON CONFLICT (id) DO NOTHING; executeUpdate intoarce numarul de randuri modificate.

    /**
     *
     * @param entity - entity must be not null
     * @return Optional.empty() - if the given entity is saved
     * otherwise returns an Optional with the entity (id already exists)
     * @throws curs.domain.validators.ValidationException if the entity is not valid
     * @throws IllegalArgumentException                   if the given entity is null.
     * @throws RepositoryException                        if a database access error occurs
     */
    @Override
    public Optional<Utilizator> save(Utilizator entity) {
        if (entity == null)
            throw new IllegalArgumentException("entity must be not null");
        validator.validate(entity);
        int randuri = executa(INSERT, PreparedStatement::executeUpdate,
                entity.getId(), entity.getFirstName(), entity.getLastName());
        return randuri == 0 ? Optional.of(entity) : Optional.empty();   // 0 = id-ul exista deja
    }

    // ---------------- Cerinta 7. update ----------------
    // Implementati update: validare, apoi UPDATE ... WHERE id = ?.
    // Daca nu exista utilizatorul, intoarceti Optional.of(entity).

    /**
     *
     * @param entity - entity must not be null
     * @return Optional.empty() - if the entity is updated,
     * otherwise returns an Optional with the entity - (e.g id does not exist).
     * @throws IllegalArgumentException                   if the given entity is null.
     * @throws curs.domain.validators.ValidationException if the entity is not valid.
     * @throws RepositoryException                        if a database access error occurs
     */
    @Override
    public Optional<Utilizator> update(Utilizator entity) {
        if (entity == null)
            throw new IllegalArgumentException("entity must be not null!");
        validator.validate(entity);
        int randuri = executa(UPDATE, PreparedStatement::executeUpdate,
                entity.getFirstName(), entity.getLastName(), entity.getId());
        return randuri == 0 ? Optional.of(entity) : Optional.empty();
    }

    // ---------------- Cerinta 8. delete ----------------
    // Implementati delete(id): intoarce utilizatorul sters (Optional) sau Optional.empty().
    // Indiciu: findOne, apoi DELETE doar daca exista (ifPresent).

    /**
     *
     * @param id - id must be not null
     * @return an Optional with the removed user
     * or Optional.empty() - if there is no user with the given id
     * @throws IllegalArgumentException if the given id is null.
     * @throws RepositoryException      if a database access error occurs
     */
    @Override
    public Optional<Utilizator> delete(Long id) {
        Optional<Utilizator> gasit = findOne(id);
        gasit.ifPresent(u -> executa(DELETE, PreparedStatement::executeUpdate, id));
        return gasit;
    }
}
