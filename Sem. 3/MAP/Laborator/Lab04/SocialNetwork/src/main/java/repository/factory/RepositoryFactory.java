package repository.factory;

import domain.Friendship;
import domain.FriendshipId;
import domain.User;
import repository.Repository;
import validation.Validator;

/**
 * Creates a family of repositories using the same persistence backend.
 * */
public interface RepositoryFactory {
    /**
     * @param validator user validation strategy
     * @return a new user repository
     * */
    Repository<Long, User> createUserRepository(Validator<User> validator);

    /**
     * @param validator friendship validation strategy
     * @return a new friendship repository
     * */
    Repository<FriendshipId, Friendship> createFriendshipRepository(Validator<Friendship> validator);
}
