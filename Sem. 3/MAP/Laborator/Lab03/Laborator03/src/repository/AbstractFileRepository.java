package repository;

import domain.Entity;
import validation.ValidationException;
import validation.Validator;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.util.*;

public abstract class AbstractFileRepository<ID, E extends Entity<ID>> implements Repository<ID, E>{
    private final Path file;
    private Map<ID, E> entities = new HashMap<>();

    protected AbstractFileRepository(String file) {
        this.file = Path.of(file).toAbsolutePath();
    }

    protected abstract E fromCsv(String line);

    protected abstract String toCsv(E entity);

    protected final void loadFromFile() {
        if (Files.notExists(file)) {
            return;
        }

        Map<ID, E> loaded = new HashMap<>();
        try{
            List<String> lines = Files.readAllLines(file, StandardCharsets.UTF_8);
            for(int index = 0; index < lines.size(); index++) {
                String line = lines.get(index);
                if(line.isEmpty()) continue;

                try{
                    E entity = fromCsv(line);

                    if(loaded.putIfAbsent(entity.getId(), entity) != null) {
                        throw new IllegalArgumentException("Duplicate entry found for " + entity.getId());
                    }
                }

                catch(IllegalArgumentException | ValidationException e){
                    throw new RepositoryException("Invalid data in " + file + "at line " + (index+1), e);
                }
            }

            entities = loaded;
        }
        catch (IOException e){
            throw new RepositoryException("Error reading file " + file, e);
        }
    }

    private void persist(Map<ID, E> updated) {
        List<String> lines = new ArrayList<>();

        for (E entity : updated.values()) {
            lines.add(toCsv(entity));
        }

        Path temporaryFile = null;

        try {
            Files.createDirectories(file.getParent());

            temporaryFile = Files.createTempFile(file.getParent(),"repository-",".tmp");

            Files.write(temporaryFile, lines, StandardCharsets.UTF_8);

            Files.move(temporaryFile, file, StandardCopyOption.REPLACE_EXISTING, StandardCopyOption.ATOMIC_MOVE);

            entities = updated;
        }
        catch (IOException e) {
            throw new RepositoryException("Error saving file " + file, e);
        }
        finally {
            if (temporaryFile != null) {
                try {
                    Files.deleteIfExists(temporaryFile);
                }
                catch (IOException ignored) {}
            }
        }
    }

    @Override
    public E findOne(ID id) {
        Objects.requireNonNull(id, "ID cannot be null");
        return entities.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return new ArrayList<>(entities.values());
    }

    @Override
    public E save(E entity) {
        Objects.requireNonNull(entity, "Entity cannot be null");

        E existing = entities.get(entity.getId());

        if (existing != null) {
            return existing;
        }

        Map<ID, E> updated = new HashMap<>(entities);
        updated.put(entity.getId(), entity);
        persist(updated);

        return null;
    }

    @Override
    public E update(E entity) {
        Objects.requireNonNull(entity, "Entity cannot be null");

        if (!entities.containsKey(entity.getId())) {
            return entity;
        }

        Map<ID, E> updated = new HashMap<>(entities);
        updated.put(entity.getId(), entity);
        persist(updated);

        return null;
    }

    @Override
    public E delete(ID id){
        Objects.requireNonNull(id, "ID cannot be null");

        E existing = entities.get(id);
        if(existing == null) {
            return null;
        }

        Map<ID, E> updated = new HashMap<>(entities);
        updated.remove(id);
        persist(updated);

        return existing;
    }
}
