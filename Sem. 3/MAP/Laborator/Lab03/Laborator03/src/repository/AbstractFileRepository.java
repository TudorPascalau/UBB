package repository;

import domain.Entity;
import validation.Validator;

import java.nio.file.Path;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

public abstract class AbstractFileRepository<ID, E extends Entity<ID>> implements Repository<ID, E>{
    private final Path file;
    private final Validator<E> validator;
    private Map<ID, E> entities = new HashMap<>();

    protected AbstractFileRepository(Path file, Validator<E> validator) {
        this.file = file;
        this.validator = Objects.requireNonNull(validator, "Validator cannot be null");
    }

    protected abstract E fromCsv(String line);

    protected abstract String toCsv(E entity);

    protected final void loadFromFile() {
    }
}
