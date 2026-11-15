package repository.db;

import domain.User;
import repository.Repository;
import repository.RepositoryException;
import validation.Validator;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

/**
 * Database repository for users.
 */
public final class UserDbRepository implements Repository<Long, User> {
    private final Validator<User> validator;
    private final String url;
    private final String user;
    private final String password;

    /**
     * Creates a user database repository.
     *
     * @param validator user validation strategy
     * @param url database connection URL
     * @param user database username
     * @param password database password
     * @throws IllegalArgumentException if any argument is null
     */
    public UserDbRepository(Validator<User> validator, String url, String user, String password) {
        if (validator == null || url == null || user == null || password == null) {
            throw new IllegalArgumentException("Database repository arguments cannot be null");
        }
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    @Override
    public Optional<User> findOne(Long id) {
        if(id == null) {
            throw new IllegalArgumentException("User id cannot be null");
        }

        String sql = "SELECT id, first_name, last_name FROM users WHERE id = ?";

        try(Connection connection = DriverManager.getConnection(url, user, password);
            PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setLong(1, id);

            try(ResultSet resultSet = statement.executeQuery()) {
                if(resultSet.next()) {
                    User user = readUser(resultSet);
                    return Optional.of(user);
                }

                return Optional.empty();
            }
        }
        catch (SQLException e) {
            throw new RepositoryException("Could not find user: " + e.getMessage(), e);
        }
    }

    @Override
    public Iterable<User> findAll() {
        String sql = "SELECT id, first_name, last_name FROM users ORDER BY id";
        List<User> users = new ArrayList<>();

        try(Connection connection = DriverManager.getConnection(url, user, password);
            PreparedStatement statement = connection.prepareStatement(sql)) {

            try(ResultSet resultSet = statement.executeQuery()) {
                while(resultSet.next()) {
                    User user = readUser(resultSet);
                    users.add(user);
                }

                return users;
            }
        }
        catch (SQLException e) {
            throw new RepositoryException("Could not read users: " + e.getMessage(), e);
        }
    }

    /**
     * Inserts a new user and assigns the database-generated ID to it.
     *
     * @param entity new user whose provisional ID is replaced on success
     * @return an empty Optional after insertion
     * @throws IllegalArgumentException if entity is null
     * @throws validation.ValidationException if the user is invalid
     * @throws RepositoryException if insertion or key retrieval fails
     */
    @Override
    public Optional<User> save(User entity) {
        if(entity == null) {
            throw new IllegalArgumentException("User entity cannot be null");
        }

        validator.validate(entity);

        String sql = "INSERT INTO users (first_name, last_name) VALUES (?, ?)";

        try (Connection connection = DriverManager.getConnection(url, user, password);
            PreparedStatement statement = connection.prepareStatement(sql,  Statement.RETURN_GENERATED_KEYS)) {

            statement.setString(1, entity.getFirstName());
            statement.setString(2, entity.getLastName());
            statement.executeUpdate();

            try (ResultSet resultSet = statement.getGeneratedKeys()) {
                if(!resultSet.next()) {
                    throw new RepositoryException("PostgreSQL generated key not found");
                }
                entity.setId(resultSet.getLong("id"));
            }

            return Optional.empty();

        }
        catch (SQLException e) {
            throw new RepositoryException("Could not save user: " + e.getMessage(), e);
        }
    }

    /**
     * Updates an existing user.
     *
     * @param entity replacement with the ID of the user to update
     * @return an empty Optional on success, or the supplied user if its ID is absent
     * @throws IllegalArgumentException if entity is null
     * @throws validation.ValidationException if the user is invalid
     * @throws RepositoryException if the update fails
     */
    @Override
    public Optional<User> update(User entity) {
        if (entity == null) {
            throw new IllegalArgumentException("User entity cannot be null");
        }
        validator.validate(entity);

        String sql = "UPDATE users SET first_name = ?, last_name = ? WHERE id = ?";

        try (Connection connection = DriverManager.getConnection(url, user, password);
            PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setString(1, entity.getFirstName());
            statement.setString(2, entity.getLastName());
            statement.setLong(3, entity.getId());

            if (statement.executeUpdate() == 0) {
                return Optional.of(entity);
            }
            return Optional.empty();
        }
        catch (SQLException e) {
            throw new RepositoryException("Could not update user: " + e.getMessage(), e);
        }
    }

    /**
     * Deletes a user by ID.
     *
     * @param id ID of the user to delete
     * @return the deleted user, or an empty Optional if the ID is absent
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if deletion fails
     */
    @Override
    public Optional<User> delete(Long id) {
        if (id == null) {
            throw new IllegalArgumentException("User id cannot be null");
        }

        String sql = "DELETE FROM users WHERE id = ? RETURNING id, first_name, last_name";

        try (Connection connection = DriverManager.getConnection(url, user, password);
            PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setLong(1, id);

            try (ResultSet resultSet = statement.executeQuery()) {
                if(resultSet.next()) {
                    User user = readUser(resultSet);
                    return Optional.of(user);
                }

                return Optional.empty();
            }
        }
        catch (SQLException e) {
            throw new RepositoryException("Could not delete user: " + e.getMessage(), e);
        }
    }

    private User readUser(ResultSet resultSet) throws SQLException {
        return new User(
                resultSet.getLong("id"),
                resultSet.getString("first_name"),
                resultSet.getString("last_name"));
    }
}
