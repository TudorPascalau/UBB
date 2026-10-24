package repository.factory;

import domain.Friendship;
import domain.FriendshipId;
import domain.User;
import repository.Repository;
import repository.RepositoryException;
import validation.Validator;

/**
 * Creates a family of repositories using the same persistence backend.
 * */
public interface RepositoryFactory {
    /**
     * Creates a user repository for this factory's persistence backend.
     * @param validator user validation strategy
     * @return a new user repository
     * @throws IllegalArgumentException if the validator is null for FILE or DATABASE,
     *         or the configured FILE path is absolute or invalid
     * @throws NullPointerException if the validator is null for MEMORY
     * @throws RepositoryException if FILE data cannot be read or contains invalid or duplicate records
     * */
    Repository<Long, User> createUserRepository(Validator<User> validator);

    /**
     * Creates a friendship repository for this factory's persistence backend.
     * @param validator friendship validation strategy
     * @return a new friendship repository
     * @throws IllegalArgumentException if the validator is null for FILE or DATABASE,
     *         or the configured FILE path is absolute or invalid
     * @throws NullPointerException if the validator is null for MEMORY
     * @throws RepositoryException if FILE data cannot be read or contains invalid or duplicate records
     * */
    Repository<FriendshipId, Friendship> createFriendshipRepository(Validator<Friendship> validator);
}
