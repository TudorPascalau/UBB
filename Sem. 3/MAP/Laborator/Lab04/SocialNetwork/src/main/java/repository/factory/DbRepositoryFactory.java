package repository.factory;

import domain.Friendship;
import domain.FriendshipId;
import domain.User;
import repository.Repository;
import repository.db.FriendshipDbRepository;
import repository.db.UserDbRepository;
import validation.Validator;
import java.util.Objects;

/**
 * Creates database repository skeletons without opening a connection.
 * */
public final class DbRepositoryFactory implements RepositoryFactory {
    private final String url;
    private final String user;
    private final String password;

    /**
     * @param url database connection URL
     * @param user database username
     * @param password database password
     */
    public DbRepositoryFactory(String url, String user, String password) {
        this.url = Objects.requireNonNull(url);
        this.user = Objects.requireNonNull(user);
        this.password = Objects.requireNonNull(password);
    }

    @Override
    public Repository<Long, User> createUserRepository(Validator<User> validator) {
        return new UserDbRepository(validator, url, user, password);
    }

    @Override
    public Repository<FriendshipId, Friendship> createFriendshipRepository(Validator<Friendship> validator) {
        return new FriendshipDbRepository(validator, url, user, password);
    }
}
