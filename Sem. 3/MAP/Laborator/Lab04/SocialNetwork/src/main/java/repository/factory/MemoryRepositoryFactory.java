package repository.factory;

import domain.Friendship;
import domain.FriendshipId;
import domain.User;
import repository.InMemoryRepository;
import repository.Repository;

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
     */
    @Override
    public Repository<Long, User> createUserRepository() {
        return new InMemoryRepository<>();
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Repository<FriendshipId, Friendship> createFriendshipRepository() {
        return new InMemoryRepository<>();
    }
}
