package repository.db;

import domain.User;
import domain.validators.Validator;
import repository.Repository;

public class UserDbRepository implements Repository<Long, User> {

    private Validator<User> validator;
    private String url;
    private String user;
    private String password;

    public UserDbRepository(Validator<User> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    @Override
    public User findOne(Long aLong) {
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
    public User delete(Long aLong) {
        throw new UnsupportedOperationException("delete nu este implementat inca");
    }

    @Override
    public User update(User entity) {
        throw new UnsupportedOperationException("update nu este implementat inca");
    }
}
