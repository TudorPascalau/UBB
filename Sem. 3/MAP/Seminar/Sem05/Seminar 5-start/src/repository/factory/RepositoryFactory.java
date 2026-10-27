package repository.factory;

import domain.User;
import domain.validators.Validator;
import repository.InMemoryRepository;
import repository.Repository;
import repository.db.UserDBRepository;
import repository.file.UserFileRepository;

import java.util.Map;
import java.util.Properties;
import java.util.function.Supplier;

/**
 * Simple factory: the only place that knows the concrete repository classes.
 */
public class RepositoryFactory {

    private final Properties properties;

    public RepositoryFactory(Properties properties) {
        this.properties = properties;
    }

    public Repository<Long, User> createUserRepository(Validator<User> validator) {
        String value = properties.getProperty("repository.type");
        if (value == null) {
            throw new IllegalArgumentException("The key repository.type is missing from the properties file");
        }

        RepositoryType type = RepositoryType.valueOf(value.trim().toUpperCase());

        Map<RepositoryType, Supplier<Repository<Long, User>>> map = Map.of(
                RepositoryType.MEMORY, ()->new InMemoryRepository<>(validator),
                RepositoryType.FILE, ()->new UserFileRepository(validator, properties.getProperty("file.users")),
                RepositoryType.DATABASE, () -> new UserDBRepository(validator,
                        properties.getProperty("db.url"),
                        properties.getProperty("db.user"),
                        properties.getProperty("db.password"))
        );

        Supplier<Repository<Long, User>> supplier = map.get(type);
        if (supplier == null) {
            throw new IllegalArgumentException("The key repository.type is missing from the properties file");
        }

        switch (type) {
            case MEMORY:
                return new InMemoryRepository<>(validator);
            case FILE:
                return new UserFileRepository(validator, properties.getProperty("file.users"));
            case DATABASE:
                return new UserDBRepository(validator, properties.getProperty("db.url"),
                        properties.getProperty("db.user"),
                        properties.getProperty("db.password"));
            default:
                throw new IllegalArgumentException("Unknown repository type");
        }
    }
}
