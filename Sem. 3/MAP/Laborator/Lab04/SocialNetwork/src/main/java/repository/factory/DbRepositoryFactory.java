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
    private final Validator<User> userValidator;
    private final Validator<Friendship> friendshipValidator;

    /**
     * Stores connection parameters without opening a database connection.
     * @param url database connection URL
     * @param user database username
     * @param password database password
     * @param userValidator user validation strategy
     * @param friendshipValidator friendship validation strategy
     * @throws NullPointerException if any argument is null
     */
    public DbRepositoryFactory(String url, String user, String password,
                               Validator<User> userValidator, Validator<Friendship> friendshipValidator) {
        this.url = Objects.requireNonNull(url);
        this.user = Objects.requireNonNull(user);
        this.password = Objects.requireNonNull(password);
        this.userValidator = Objects.requireNonNull(userValidator);
        this.friendshipValidator = Objects.requireNonNull(friendshipValidator);
    }

    @Override
    public Repository<Long, User> createUserRepository() {
        return new UserDbRepository(userValidator, url, user, password);
    }

    @Override
    public Repository<FriendshipId, Friendship> createFriendshipRepository() {
        return new FriendshipDbRepository(friendshipValidator, url, user, password);
    }
}
