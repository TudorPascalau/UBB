package repository.factory;

import domain.Friendship;
import domain.FriendshipId;
import domain.User;
import repository.Repository;
import repository.file.FriendshipFileRepository;
import repository.file.UserFileRepository;
import validation.Validator;
import java.util.Objects;

/**
 * Creates file repositories using configured paths and validation strategies.
 * */
public final class FileRepositoryFactory implements RepositoryFactory {
    private final String usersPath;
    private final String friendshipsPath;
    private final Validator<User> userValidator;
    private final Validator<Friendship> friendshipValidator;

    /**
     * Stores paths and validators; path format and file contents are checked when repositories are created.
     * @param usersPath relative path to user data
     * @param friendshipsPath relative path to friendship data
     * @param userValidator user validation strategy
     * @param friendshipValidator friendship validation strategy
     * @throws NullPointerException if any argument is null
     */
    public FileRepositoryFactory(String usersPath, String friendshipsPath,
                                 Validator<User> userValidator, Validator<Friendship> friendshipValidator) {
        this.usersPath = Objects.requireNonNull(usersPath);
        this.friendshipsPath = Objects.requireNonNull(friendshipsPath);
        this.userValidator = Objects.requireNonNull(userValidator);
        this.friendshipValidator = Objects.requireNonNull(friendshipValidator);
    }

    @Override
    public Repository<Long, User> createUserRepository() {
        return new UserFileRepository(usersPath, userValidator);
    }

    @Override
    public Repository<FriendshipId, Friendship> createFriendshipRepository() {
        return new FriendshipFileRepository(friendshipsPath, friendshipValidator);
    }
}
