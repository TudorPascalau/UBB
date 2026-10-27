package config;

import repository.RepositoryType;
import repository.factory.RepositoryFactory;
import repository.factory.MemoryRepositoryFactory;
import repository.factory.FileRepositoryFactory;
import repository.factory.DbRepositoryFactory;
import domain.User;
import domain.Friendship;
import validation.Validator;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.Properties;

/** Reads UTF-8 application properties and selects a repository family. */
public final class ConfigLoader {
    private ConfigLoader() {}

    /**
     * Reads configuration using a BufferedReader and creates the selected factory.
     * @param fileName configuration file path, relative to the working directory
     * @param userValidator user validation strategy, required for FILE and DATABASE
     * @param friendshipValidator friendship validation strategy, required for FILE and DATABASE
     * @return a factory for the configured persistence backend
     * @throws IOException if the configuration cannot be read
     * @throws IllegalArgumentException if a required property is missing or invalid
     * @throws NullPointerException if a validator is null for FILE or DATABASE
     */
    public static RepositoryFactory loadFactory(String fileName, Validator<User> userValidator,
                                                 Validator<Friendship> friendshipValidator) throws IOException {
        Properties properties = new Properties();
        try (BufferedReader reader = new BufferedReader(new FileReader(fileName, StandardCharsets.UTF_8))) {
            properties.load(reader);
        }

        String configuredType = required(properties, "repository.type");
        RepositoryType type;
        try {
            type = RepositoryType.valueOf(configuredType);
        }
        catch (IllegalArgumentException e) {
            throw new IllegalArgumentException("Unknown repository.type: " + configuredType
                    + ". Expected MEMORY, FILE or DATABASE", e);
        }

        switch (type) {
            case MEMORY:
                return new MemoryRepositoryFactory();
            case FILE:
                return new FileRepositoryFactory(required(properties, "repository.users.file"),
                        required(properties, "repository.friendships.file"), userValidator, friendshipValidator);
            case DATABASE:
                return new DbRepositoryFactory(required(properties, "db.url"),
                        required(properties, "db.user"), required(properties, "db.password"),
                        userValidator, friendshipValidator);
            default:
                throw new IllegalArgumentException("Unsupported repository type: " + type);
        }
    }

    private static String required(Properties properties, String key) {
        String value = properties.getProperty(key);
        if (value == null || value.isBlank()) {
            throw new IllegalArgumentException("Missing or empty configuration property: " + key);
        }
        return value.trim();
    }
}
