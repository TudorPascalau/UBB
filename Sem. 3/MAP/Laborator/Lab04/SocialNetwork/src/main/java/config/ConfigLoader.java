package config;

import repository.RepositoryType;
import repository.factory.RepositoryFactory;
import repository.factory.MemoryRepositoryFactory;
import repository.factory.FileRepositoryFactory;
import repository.factory.DbRepositoryFactory;
import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

/** Reads application properties and selects a repository family. */
public final class ConfigLoader {
    private ConfigLoader() {}

    /**
     * Reads configuration using a Reader and creates the selected factory.
     * @param fileName configuration file path, relative to the working directory
     * @return a factory for the configured persistence backend
     * @throws IOException if the configuration cannot be read
     * @throws IllegalArgumentException if a required property is missing or invalid
     */
    public static RepositoryFactory loadFactory(String fileName) throws IOException {
        Properties properties = new Properties();
        try (FileReader reader = new FileReader(fileName)) {
            properties.load(reader);
        }

        String configuredType = required(properties, "repository.type");
        RepositoryType type;
        try {
            type = RepositoryType.valueOf(configuredType);
        } catch (IllegalArgumentException e) {
            throw new IllegalArgumentException("Unknown repository.type: " + configuredType
                    + ". Expected MEMORY, FILE or DATABASE", e);
        }

        switch (type) {
            case MEMORY:
                return new MemoryRepositoryFactory();
            case FILE:
                return new FileRepositoryFactory(required(properties, "repository.users.file"),
                        required(properties, "repository.friendships.file"));
            case DATABASE:
                return new DbRepositoryFactory(required(properties, "db.url"),
                        required(properties, "db.user"), required(properties, "db.password"));
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
