package repository.file;

import domain.Entity;
import repository.InMemoryRepository;
import repository.RepositoryException;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.time.format.DateTimeParseException;
import java.util.Map;

/**
 * Stores entities in a UTF-8 text file; rejects malformed records and duplicate identifiers.
 * @param <ID> identifier type
 * @param <E> entity type
 */
public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {
    private final Path file;

    /**
     * Creates a repository for the given file; subclasses must call loadData after initialization.
     * @param fileName relative text file path
     * @throws IllegalArgumentException if the path is absolute
     */
    protected AbstractFileRepository(String fileName) {
        file = Path.of(fileName);
        if (file.isAbsolute()) throw new IllegalArgumentException("Use a relative data path");
    }
    /**
     * Builds an entity from one text record.
     * @param line input record
     * @return the parsed entity
     * @throws IllegalArgumentException if the record has an invalid format
     * @throws java.time.format.DateTimeParseException if its date is invalid
     */
    protected abstract E extractEntity(String line);
    /**
     * Converts an entity to its persistent text representation.
     * @param entity entity to encode
     * @return the text record
     */
    protected abstract String createEntityAsString(E entity);

    /**
     * Loads stored entities after subclass initialization. A missing file leaves the repository unchanged.
     * @throws RepositoryException if reading fails or a record is invalid or duplicates an identifier
     */
    protected final void loadData() {
        Map<ID, E> previous = snapshot();
        try (BufferedReader reader = Files.newBufferedReader(file, StandardCharsets.UTF_8)) {
            String line;
            int number = 0;
            while ((line = reader.readLine()) != null) {
                number++;
                if (line.isBlank()) continue;
                try {
                    E entity = extractEntity(line);
                    // Deliberately bypass file save: loading must not rewrite the input.
                    if (super.save(entity) != null)
                        throw new IllegalArgumentException("Duplicate ID: " + entity.getId());
                }
                catch (IllegalArgumentException | DateTimeParseException e) {
                    throw new RepositoryException("Invalid data in " + file + " at line "
                            + number + ": " + e.getMessage(), e);
                }
            }
        } catch (NoSuchFileException e) {
            restore(previous);
            // Missing input is an expected empty state; first save creates the file.
        } catch (IOException e) {
            restore(previous);
            throw new RepositoryException("Error reading " + file, e);
        } catch (RepositoryException e) {
            restore(previous);
            throw e;
        }
    }


    private void writeToFile() {
        Path temporary = null;
        try {
            Path parent = file.getParent();
            if (parent == null) parent = Path.of(".");
            Files.createDirectories(parent);
            temporary = Files.createTempFile(parent, "repository-", ".tmp");

            try (BufferedWriter writer = Files.newBufferedWriter(temporary, StandardCharsets.UTF_8)) {
                for (E entity : findAll()) {
                    writer.write(createEntityAsString(entity));
                    writer.newLine();
                }
            }
            Files.move(temporary, file, StandardCopyOption.REPLACE_EXISTING, StandardCopyOption.ATOMIC_MOVE);

        }
        catch (IOException e) {
            if (temporary != null) {
                try { Files.deleteIfExists(temporary); }
                catch (IOException cleanupError) { e.addSuppressed(cleanupError); }
            }
            throw new RepositoryException("Error saving " + file, e);
        }
    }

    @Override public E save(E entity) {
        Map<ID, E> previous = snapshot();
        E result = super.save(entity);
        if (result == null) persistOrRestore(previous);
        return result;
    }

    @Override public E update(E entity) {
        Map<ID, E> previous = snapshot();
        E result = super.update(entity);
        if (result == null) persistOrRestore(previous);
        return result;
    }

    @Override public E delete(ID id) {
        Map<ID, E> previous = snapshot();
        E result = super.delete(id);
        if (result != null) persistOrRestore(previous);
        return result;
    }


    private void persistOrRestore(Map<ID, E> previous) {
        try { writeToFile(); }
        catch (RepositoryException e) {
            restore(previous);
            throw e;
        }
    }
}
