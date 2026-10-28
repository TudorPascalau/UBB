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
import java.util.Objects;
import java.util.Properties;

/** Creates user and friendship repositories for the configured persistence backend. */
public final class RepositoryFactory {
    private final Properties properties;
    private final RepositoryType type;

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
        } catch (IllegalArgumentException e) {
            throw new IllegalArgumentException("Unknown repository.type: " + configuredType
                    + ". Expected MEMORY, FILE or DATABASE", e);
        }
        if (type == RepositoryType.FILE) {
            required("repository.users.file");
            required("repository.friendships.file");
        } else if (type == RepositoryType.DATABASE) {
            required("db.url");
            required("db.user");
            required("db.password");
        }
    }

    /**
     * Creates a user repository for this factory's persistence backend.
     * @param validator user validation strategy
     * @return a new user repository
     * @throws IllegalArgumentException if the validator is null for FILE or DATABASE,
     *         or the configured FILE path is absolute or invalid
     * @throws NullPointerException if the validator is null for MEMORY
     * @throws RepositoryException if FILE data cannot be read or contains invalid or duplicate records
     * */
    public Repository<Long, User> createUserRepository(Validator<User> validator) {
        switch (type) {
            case MEMORY:
                Objects.requireNonNull(validator, "User validator cannot be null");
                return new InMemoryRepository<>();
            case FILE:
                return new UserFileRepository(required("repository.users.file"), validator);
            case DATABASE:
                return new UserDbRepository(validator, required("db.url"),
                        required("db.user"), required("db.password"));
            default:
                throw new IllegalArgumentException("Unsupported repository type: " + type);
        }
    }

    /**
     * Creates a friendship repository for this factory's persistence backend.
     * @param validator friendship validation strategy
     * @return a new friendship repository
     * @throws IllegalArgumentException if the validator is null for FILE or DATABASE,
     *         or the configured FILE path is absolute or invalid
     * @throws NullPointerException if the validator is null for MEMORY
     * @throws RepositoryException if FILE data cannot be read or contains invalid or duplicate records
     * */
    public Repository<FriendshipId, Friendship> createFriendshipRepository(Validator<Friendship> validator) {
        switch (type) {
            case MEMORY:
                Objects.requireNonNull(validator, "Friendship validator cannot be null");
                return new InMemoryRepository<>();
            case FILE:
                return new FriendshipFileRepository(required("repository.friendships.file"), validator);
            case DATABASE:
                return new FriendshipDbRepository(validator, required("db.url"),
                        required("db.user"), required("db.password"));
            default:
                throw new IllegalArgumentException("Unsupported repository type: " + type);
        }
    }

    private String required(String key) {
        String value = properties.getProperty(key);
        if (value == null || value.isBlank()) {
            throw new IllegalArgumentException("Missing or empty configuration property: " + key);
        }
        return value.trim();
    }
}
