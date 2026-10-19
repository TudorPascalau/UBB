package home;

import domain.User;
import domain.validators.Validator;
import repository.Repository;

/**
 * Requirement 4: database repository skeleton, to be implemented with JDBC later.
 * The database is the source of data, so this class does not extend InMemoryRepository.
 */
public class UserDbRepository implements Repository<Long, User> {
    private final Validator<User> validator;
    private final String url;
    private final String user;
    private final String password;

    public UserDbRepository(Validator<User> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    @Override
    public User findOne(Long id) {
        throw new UnsupportedOperationException("findOne nu este implementat inca");
    }

    @Override
    public Iterable<User> findAll() {
        throw new UnsupportedOperationException("findAll nu este implementat inca");
    }

    @Override
    public User save(User entity) {
        throw new UnsupportedOperationException("save nu este implementat inca");
    }

    @Override
    public User delete(Long id) {
        throw new UnsupportedOperationException("delete nu este implementat inca");
    }

    @Override
    public User update(User entity) {
        throw new UnsupportedOperationException("update nu este implementat inca");
    }
}
