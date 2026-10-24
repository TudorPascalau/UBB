package repository.db;

import domain.User;
import validation.Validator;
import repository.Repository;

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

    /** @throws UnsupportedOperationException because database access is not implemented */
    @Override
    public User findOne(Long id) {
        throw new UnsupportedOperationException("Database access is not implemented yet");
    }

    /** @throws UnsupportedOperationException because database access is not implemented */
    @Override
    public Iterable<User> findAll() {
        throw new UnsupportedOperationException("Database access is not implemented yet");
    }

    /** @throws UnsupportedOperationException because database access is not implemented */
    @Override
    public User save(User entity) {
        throw new UnsupportedOperationException("Database access is not implemented yet");
    }

    /** @throws UnsupportedOperationException because database access is not implemented */
    @Override
    public User update(User entity) {
        throw new UnsupportedOperationException("Database access is not implemented yet");
    }

    /** @throws UnsupportedOperationException because database access is not implemented */
    @Override
    public User delete(Long id) {
        throw new UnsupportedOperationException("Database access is not implemented yet");
    }
}
