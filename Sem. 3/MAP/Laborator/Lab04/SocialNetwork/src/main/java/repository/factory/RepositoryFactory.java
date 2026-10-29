package repository.factory;

import domain.Friendship;
import domain.FriendshipId;
import domain.User;
import repository.Repository;
import repository.RepositoryException;
import repository.RepositoryType;
import repository.InMemoryRepository;
import repository.file.UserFileRepository;
import repository.file.FriendshipFileRepository;
import repository.db.UserDbRepository;
import repository.db.FriendshipDbRepository;
import validation.Validator;

import java.util.EnumMap;
import java.util.Map;
import java.util.Properties;
import java.util.function.Function;

/** Creates user and friendship repositories for the configured persistence backend. */
public final class RepositoryFactory {
    private final Properties properties;
    private final RepositoryType type;

    private final Map<RepositoryType, Function<Validator<User>, Repository<Long, User>>
                > userCreators = new EnumMap<>(RepositoryType.class);

    private final Map<RepositoryType, Function<Validator<Friendship>, Repository<FriendshipId, Friendship>>
                > friendshipCreators = new EnumMap<>(RepositoryType.class);

    /**
     * Copies configuration and validates the properties required by the selected backend.
     * @param properties application configuration loaded from a properties file
     * @throws IllegalArgumentException if properties is null, the type is unknown,
     *         or a required property is missing or blank
     */
    public RepositoryFactory(Properties properties) {
        if (properties == null) {
            throw new IllegalArgumentException("Properties cannot be null");
        }
        this.properties = new Properties();
        this.properties.putAll(properties);

        String configuredType = required("repository.type");
        try {
            type = RepositoryType.valueOf(configuredType);
        }
        catch (IllegalArgumentException e) {
            throw new IllegalArgumentException("Unknown repository.type: " + configuredType
                    + ". Expected MEMORY, FILE or DATABASE", e);
        }

        if (type == RepositoryType.FILE) {
            required("repository.users.file");
            required("repository.friendships.file");
        }
        else if (type == RepositoryType.DATABASE) {
            required("db.url");
            required("db.user");
            required("db.password");
        }

        userCreators.put(RepositoryType.MEMORY, InMemoryRepository::new);

        userCreators.put(RepositoryType.FILE, validator -> new UserFileRepository(
                        required("repository.users.file"),
                        validator)
        );

        userCreators.put(RepositoryType.DATABASE,  validator -> new UserDbRepository(
                        validator,
                        required("db.url"),
                        required("db.user"),
                        required("db.password"))
        );

        friendshipCreators.put(RepositoryType.MEMORY, InMemoryRepository::new);

        friendshipCreators.put(RepositoryType.FILE, validator -> new FriendshipFileRepository(
                        required("repository.friendships.file"),
                        validator)
        );

        friendshipCreators.put(RepositoryType.DATABASE, validator -> new FriendshipDbRepository(
                        validator,
                        required("db.url"),
                        required("db.user"),
                        required("db.password"))
        );
    }

    /**
     * Creates a user repository for the configured persistence backend.
     *
     * @param validator user validation strategy passed to the selected creator
     * @return a new user repository
     * @throws IllegalArgumentException if validator is null,
     *         a required property is missing or blank,
     *         or the configured FILE path is absolute or invalid
     * @throws RepositoryException if FILE data cannot be read
     *         or contains invalid or duplicate records
     */
    public Repository<Long, User> createUserRepository(Validator<User> validator) {

        Function<Validator<User>, Repository<Long, User>> creator = userCreators.get(type);

        if (creator == null) {
            throw new IllegalArgumentException("Unsupported repository type: " + type);
        }

        return creator.apply(validator);
    }

    /**
     * Creates a friendship repository for the configured persistence backend.
     *
     * @param validator friendship validation strategy passed to the selected creator
     * @return a new friendship repository
     * @throws IllegalArgumentException if validator is null,
     *         a required property is missing or blank,
     *         or the configured FILE path is absolute or invalid
     * @throws RepositoryException if FILE data cannot be read
     *         or contains invalid or duplicate records
     */
    public Repository<FriendshipId, Friendship> createFriendshipRepository(Validator<Friendship> validator) {

        Function<Validator<Friendship>, Repository<FriendshipId, Friendship>> creator =friendshipCreators.get(type);

        if (creator == null) {
            throw new IllegalArgumentException("Unsupported repository type: " + type);
        }

        return creator.apply(validator);
    }

    private String required(String key) {
        String value = properties.getProperty(key);
        if (value == null || value.isBlank()) {
            throw new IllegalArgumentException("Missing or empty configuration property: " + key);
        }
        return value.trim();
    }
}
