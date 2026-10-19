package home;

import domain.User;
import domain.validators.Validator;
import repository.InMemoryRepository;
import repository.Repository;
import repository.file.UserFileRepository;

import java.util.Properties;

/**
 * Requirement 5: Simple Factory. Only the factory chooses concrete repositories;
 * callers depend on the Repository interface and external configuration.
 */
public class RepositoryFactory {
    private final Properties properties;

    public RepositoryFactory(Properties properties) {
        if (properties == null)
            throw new IllegalArgumentException("Configuratia nu poate fi null");
        this.properties = properties;
    }

    public Repository<Long, User> createUserRepository(Validator<User> validator) {
        String configuredType = requiredProperty("repository.type");
        RepositoryType type;
        try {
            // Convert external text to an enum once, at the factory boundary.
            type = RepositoryType.valueOf(configuredType);
        } catch (IllegalArgumentException e) {
            throw new IllegalArgumentException("Tip de repository necunoscut: " + configuredType, e);
        }

        // Each return prevents fall-through. Read only the selected storage's parameters.
        switch (type) {
            case MEMORY:
                return new InMemoryRepository<Long, User>(validator);
            case FILE:
                return new UserFileRepository(validator, requiredProperty("file.utilizatori"));
            case DATABASE:
                return new UserDbRepository(validator, requiredProperty("db.url"),
                        requiredProperty("db.user"), databasePassword());
            default:
                throw new IllegalArgumentException("Tip de repository necunoscut: " + type);
        }
    }

    private String requiredProperty(String key) {
        String value = properties.getProperty(key);
        if (value == null || value.isBlank())
            throw new IllegalArgumentException("Proprietate lipsa sau goala: " + key);
        return value.trim();
    }

    private String databasePassword() {
        // An empty password is valid configuration; do not trim password characters.
        String password = properties.getProperty("db.password");
        if (password == null)
            throw new IllegalArgumentException("Proprietate lipsa: db.password");
        return password;
    }
}
