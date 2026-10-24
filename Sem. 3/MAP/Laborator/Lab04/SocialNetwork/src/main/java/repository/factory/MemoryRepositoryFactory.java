package repository.factory;

import domain.Friendship;
import domain.FriendshipId;
import domain.User;
import repository.InMemoryRepository;
import repository.Repository;
import validation.Validator;
import java.util.Objects;

/**
 * Creates repositories whose data lasts for the current application run.
 * */
public final class MemoryRepositoryFactory implements RepositoryFactory {
    /**
     * Creates a factory for in-memory user and friendship repositories.
     */
    public MemoryRepositoryFactory() {}

    /**
     * {@inheritDoc}
     * @throws NullPointerException if the validator is null
     */
    @Override
    public Repository<Long, User> createUserRepository(Validator<User> validator) {
        Objects.requireNonNull(validator, "User validator cannot be null");
        return new InMemoryRepository<>();
    }

    /**
     * {@inheritDoc}
     * @throws NullPointerException if the validator is null
     */
    @Override
    public Repository<FriendshipId, Friendship> createFriendshipRepository(Validator<Friendship> validator) {
        Objects.requireNonNull(validator, "Friendship validator cannot be null");
        return new InMemoryRepository<>();
    }
}
