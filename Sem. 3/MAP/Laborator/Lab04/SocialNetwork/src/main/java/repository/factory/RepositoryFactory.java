package repository.factory;

import domain.Friendship;
import domain.FriendshipId;
import domain.User;
import repository.Repository;
import repository.RepositoryException;

/**
 * Creates a family of repositories using the same persistence backend.
 * */
public interface RepositoryFactory {
    /**
     * Creates a user repository for this factory's persistence backend.
     * @return a new user repository
     * @throws IllegalArgumentException if the configured FILE path is absolute or invalid
     * @throws RepositoryException if FILE data cannot be read or contains invalid or duplicate records
     * */
    Repository<Long, User> createUserRepository();

    /**
     * Creates a friendship repository for this factory's persistence backend.
     * @return a new friendship repository
     * @throws IllegalArgumentException if the configured FILE path is absolute or invalid
     * @throws RepositoryException if FILE data cannot be read or contains invalid or duplicate records
     * */
    Repository<FriendshipId, Friendship> createFriendshipRepository();
}
