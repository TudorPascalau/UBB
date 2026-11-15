package repository.db;

import domain.Friendship;
import domain.FriendshipId;
import repository.Repository;
import repository.RepositoryException;
import validation.Validator;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

/**
 * Stores friendships in PostgreSQL using the participant IDs as a composite key.
 */
public final class FriendshipDbRepository implements Repository<FriendshipId, Friendship> {
    private final Validator<Friendship> validator;
    private final String url;
    private final String user;
    private final String password;

    /**
     * Creates a friendship database repository.
     *
     * @param validator friendship validation strategy
     * @param url database connection URL
     * @param user database username
     * @param password database password
     * @throws IllegalArgumentException if any argument is null
     */
    public FriendshipDbRepository(
            Validator<Friendship> validator, String url, String user, String password) {
        if (validator == null || url == null || user == null || password == null) {
            throw new IllegalArgumentException("Database repository arguments cannot be null");
        }
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    @Override
    public Optional<Friendship> findOne(FriendshipId id) {
        if (id == null) {
            throw new IllegalArgumentException("Friendship ID cannot be null");
        }

        String sql = "SELECT id1, id2, friends_from FROM friendships WHERE id1 = ? AND id2 = ?";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement statement = connection.prepareStatement(sql)) {

            bindId(statement, 1, id);

            try (ResultSet resultSet = statement.executeQuery()) {
                if(resultSet.next()) {
                    Friendship friendship = readFriendship(resultSet);
                    return Optional.of(friendship);
                }

                return Optional.empty();

            }
        }
        catch (SQLException e) {
            throw new RepositoryException("Could not find friendship: " + e.getMessage(), e);
        }
    }

    @Override
    public Iterable<Friendship> findAll() {
        String sql = "SELECT id1, id2, friends_from FROM friendships ORDER BY id1, id2";
        List<Friendship> friendships = new ArrayList<>();

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement statement = connection.prepareStatement(sql);
             ResultSet rows = statement.executeQuery()) {

            while (rows.next()) {
                friendships.add(readFriendship(rows));
            }

            return friendships;
        }
        catch (SQLException e) {
            throw new RepositoryException("Could not read friendships: " + e.getMessage(), e);
        }
    }

    @Override
    public Optional<Friendship> save(Friendship entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Friendship cannot be null");
        }
        validator.validate(entity);

        String sql = """
                INSERT INTO friendships (id1, id2, friends_from)
                VALUES (?, ?, ?)
                ON CONFLICT (id1, id2) DO NOTHING
                """;

        FriendshipId id = entity.getId();

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement statement = connection.prepareStatement(sql)) {

            bindId(statement, 1, id);
            statement.setObject(3, entity.getFriendsSince());

            if (statement.executeUpdate() == 1) {
                return Optional.empty();
            }
        }
        catch (SQLException e) {
            throw new RepositoryException("Could not save friendship: " + e.getMessage(), e);
        }

        Optional<Friendship> existing = findOne(id);
        if (existing.isEmpty()) {
            throw new RepositoryException("Conflicting friendship disappeared during save: " + id);
        }
        return existing;
    }

    @Override
    public Optional<Friendship> update(Friendship entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Friendship cannot be null");
        }
        validator.validate(entity);

        String sql = "UPDATE friendships SET friends_from = ? WHERE id1 = ? AND id2 = ?";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setObject(1, entity.getFriendsSince());
            bindId(statement, 2, entity.getId());

            if(statement.executeUpdate() == 0) {
                return Optional.of(entity);
            }
            return Optional.empty();
        }
        catch (SQLException e) {
            throw new RepositoryException("Could not update friendship: " + e.getMessage(), e);
        }
    }

    @Override
    public Optional<Friendship> delete(FriendshipId id) {
        if (id == null) {
            throw new IllegalArgumentException("Friendship ID cannot be null");
        }

        String sql = """
                DELETE FROM friendships
                WHERE id1 = ? AND id2 = ?
                RETURNING id1, id2, friends_from
                """;

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement statement = connection.prepareStatement(sql)) {

            bindId(statement, 1, id);

            try (ResultSet resultSet = statement.executeQuery()) {
                if(resultSet.next()) {
                    Friendship friendship = readFriendship(resultSet);
                    return Optional.of(friendship);
                }
                return Optional.empty();
            }
        }
        catch (SQLException e) {
            throw new RepositoryException("Could not delete friendship: " + e.getMessage(), e);
        }
    }

    private void bindId(PreparedStatement statement, int firstIndex, FriendshipId id) throws SQLException {
        statement.setLong(firstIndex, id.getFirstUserId());
        statement.setLong(firstIndex + 1, id.getSecondUserId());
    }

    private Friendship readFriendship(ResultSet rows) throws SQLException {
        return new Friendship(
                rows.getLong("id1"),
                rows.getLong("id2"),
                rows.getObject("friends_from", LocalDateTime.class));
    }
}
