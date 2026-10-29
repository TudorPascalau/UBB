package repository.db;

import domain.Friendship;
import domain.FriendshipId;
import validation.Validator;
import repository.Repository;

import java.util.Optional;

/**
 * Database repository for friendships.
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
    public FriendshipDbRepository(Validator<Friendship> validator, String url, String user, String password) {
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
    public Optional<Friendship> findOne(FriendshipId id) {
        throw new UnsupportedOperationException("Database access is not implemented yet");
    }

    /** @throws UnsupportedOperationException because database access is not implemented */
    @Override
    public Iterable<Friendship> findAll() {
        throw new UnsupportedOperationException("Database access is not implemented yet");
    }

    /** @throws UnsupportedOperationException because database access is not implemented */
    @Override
    public Optional<Friendship> save(Friendship entity) {
        throw new UnsupportedOperationException("Database access is not implemented yet");
    }

    /** @throws UnsupportedOperationException because database access is not implemented */
    @Override
    public Optional<Friendship> update(Friendship entity) {
        throw new UnsupportedOperationException("Database access is not implemented yet");
    }

    /** @throws UnsupportedOperationException because database access is not implemented */
    @Override
    public Optional<Friendship> delete(FriendshipId id) {
        throw new UnsupportedOperationException("Database access is not implemented yet");
    }
}
