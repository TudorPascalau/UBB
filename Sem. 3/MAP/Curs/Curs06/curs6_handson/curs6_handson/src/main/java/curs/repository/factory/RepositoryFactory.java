package curs.repository.factory;

import curs.domain.Utilizator;
import curs.domain.validators.Validator;
import curs.repository.InMemoryRepository;
import curs.repository.Repository;
import curs.repository.db.UtilizatorDbRepository;
import curs.repository.file.UtilizatorFileRepository;

import java.util.Map;
import java.util.Properties;
import java.util.function.Supplier;

/**
 * Simple Factory: the only place that knows the concrete repository classes.
 * The type of storage and its parameters are read from the configuration,
 * so changing the storage means changing the configuration, not the code.
 * Seminar 5: the switch is replaced by a map storage type -&gt; Supplier.
 */
public class RepositoryFactory {

    private final Properties props;

    /**
     *
     * @param props - the configuration (repository.type, file.utilizatori, db.url, db.user, db.password)
     */
    public RepositoryFactory(Properties props) {
        this.props = props;
    }

    /**
     * creates the user repository indicated by the "repository.type" property;
     * every storage type has a Supplier that knows how to create its repository,
     * and only the selected Supplier is called (lazy creation)
     *
     * @param validator - the validation strategy for users
     * @return a repository for users (memory, file or database)
     * @throws IllegalArgumentException if the repository type is missing or unknown
     */
    public Repository<Long, Utilizator> createUtilizatorRepository(Validator<Utilizator> validator) {
        String value = props.getProperty("repository.type");
        if (value == null)
            throw new IllegalArgumentException("lipseste proprietatea repository.type");
        RepositoryType type = RepositoryType.valueOf(value.trim().toUpperCase());

        // fiecare Supplier doar STIE sa creeze repository-ul; nimic nu se creeaza aici
        Map<RepositoryType, Supplier<Repository<Long, Utilizator>>> creatori = Map.of(
                RepositoryType.MEMORY, () -> new InMemoryRepository<>(validator),
                RepositoryType.FILE, () -> new UtilizatorFileRepository(validator,
                        props.getProperty("file.utilizatori")),
                RepositoryType.DATABASE, () -> new UtilizatorDbRepository(validator,
                        props.getProperty("db.url"),
                        props.getProperty("db.user"),
                        props.getProperty("db.password"))
        );

        Supplier<Repository<Long, Utilizator>> creator = creatori.get(type);
        if (creator == null)
            throw new IllegalArgumentException("tip de repository necunoscut: " + type);
        return creator.get();     // abia acum se creeaza repository-ul ales
    }
}
