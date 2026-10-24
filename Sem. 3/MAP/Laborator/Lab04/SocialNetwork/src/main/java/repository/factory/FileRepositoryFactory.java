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

    /**
     * Stores the paths; their format and file contents are checked when repositories are created.
     * @param usersPath relative path to user data
     * @param friendshipsPath relative path to friendship data
     * @throws NullPointerException if either path is null
     */
    public FileRepositoryFactory(String usersPath, String friendshipsPath) {
        this.usersPath = Objects.requireNonNull(usersPath);
        this.friendshipsPath = Objects.requireNonNull(friendshipsPath);
    }

    @Override
    public Repository<Long, User> createUserRepository(Validator<User> validator) {
        return new UserFileRepository(usersPath, validator);
    }

    @Override
    public Repository<FriendshipId, Friendship> createFriendshipRepository(Validator<Friendship> validator) {
        return new FriendshipFileRepository(friendshipsPath, validator);
    }
}
