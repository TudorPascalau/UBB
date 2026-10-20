package repository.factory;

import domain.User;
import domain.validators.Validator;
import repository.InMemoryRepository;
import repository.Repository;
import repository.RepositoryType;
import repository.db.UserDbRepository;
import repository.file.UserFileRepository;

import java.util.Properties;

public class RepositoryFactory {
    private Properties properties;
    public RepositoryFactory(Properties properties) {
        if(properties == null) {
            throw new IllegalArgumentException("Properties cannot be null");
        }
        this.properties = properties;
    }

    public Repository<Long, User> createUserRepository(Validator<User> validator) {
        String value = properties.getProperty("repository.type");
        RepositoryType repositoryType = RepositoryType.valueOf(value.trim().toUpperCase());

        switch (repositoryType) {
            case MEMORY:
                return new InMemoryRepository<>(validator);
            case FILE:
                return new UserFileRepository(validator, properties.getProperty("file.name"));
            case DATABASE:
                return new UserDbRepository(validator, properties.getProperty("db.url"), properties.getProperty("db.user"), properties.getProperty("db.password"));
            default:
                throw new IllegalArgumentException("Invalid repository type");
        }
    }
}
