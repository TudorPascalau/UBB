package repository.file;

import domain.Entity;
import repository.InMemoryRepository;
import repository.RepositoryException;
import validation.Validator;
import validation.ValidationException;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.UncheckedIOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.time.format.DateTimeParseException;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

import static util.StreamHelper.stream;

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
     * @param validator entity validation strategy
     * @throws IllegalArgumentException if the path or validator is null, or the path is absolute
     * @throws InvalidPathException if the path cannot be converted to a file-system path
     */
    protected AbstractFileRepository(String fileName, Validator<E> validator) {
        super(validator);
        if (fileName == null)
            throw new IllegalArgumentException("File path cannot be null");
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
     * Loads stored entities after subclass initialization, ignoring blank lines.
     * A missing file leaves the repository unchanged (empty during construction).
     * The first invalid record stops loading; the exception identifies the file and
     * physical line number and retains the original parsing or validation cause.
     * A failed load restores the state from before loading.
     * @throws RepositoryException if reading fails or a record is invalid or duplicates an identifier
     */
    protected final void loadData() {
        Map<ID, E> previous = snapshot();

        try (Stream<String> lines = Files.lines(file, StandardCharsets.UTF_8)) {
            List<String> records = lines.toList();

            IntStream.range(0, records.size()).forEach(index -> loadLine(records.get(index), index + 1));
        }
        catch (NoSuchFileException e) {
            restore(previous);
        }
        catch (UncheckedIOException e) {
            restore(previous);
            throw new RepositoryException("Error reading " + file, e.getCause());
        }
        catch (IOException e) {
            restore(previous);
            throw new RepositoryException("Error reading " + file, e);
        }
        catch (RepositoryException e) {
            restore(previous);
            throw e;
        }
    }

    /**
     * Validates and stores one physical line without rewriting the file.
     *
     * @param line text record
     * @param number one-based physical line number
     * @throws RepositoryException if the record is malformed,
     *         invalid or duplicates an identifier
     */
    private void loadLine(String line, int number) {
        if (line.isBlank()) {
            return;
        }

        try {
            E entity = extractEntity(line);

            if (super.save(entity).isPresent()) {
                throw new IllegalArgumentException(
                        "Duplicate ID: " + entity.getId());
            }
        }
        catch (IllegalArgumentException
               | DateTimeParseException
               | ValidationException e) {

            throw new RepositoryException(
                    "Invalid data in " + file + " at line "
                            + number + ": " + e.getMessage(),
                    e);
        }
    }


    /**
     * Writes the complete state to a temporary UTF-8 file and atomically replaces the target.
     * If cleanup also fails, its exception is suppressed on the original I/O cause.
     * @throws RepositoryException if writing or replacing the target fails, retaining the I/O cause
     */
    private void writeToFile() {
        Path temporary = null;
        try {
            Path parent = file.getParent();
            if (parent == null) parent = Path.of(".");
            Files.createDirectories(parent);
            temporary = Files.createTempFile(parent, "repository-", ".tmp");

            List<String> lines = stream(findAll())
                    .map(this::createEntityAsString)
                    .collect(Collectors.toList());

            Files.write(temporary, lines, StandardCharsets.UTF_8);
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

    @Override
    public Optional<E> save(E entity) {
        Map<ID, E> previous = snapshot();
        Optional<E> result = super.save(entity);

        if (result.isEmpty()) {
            persistOrRestore(previous);
        }

        return result;
    }

    @Override
    public Optional<E> update(E entity) {
        Map<ID, E> previous = snapshot();
        Optional<E> result = super.update(entity);

        if (result.isEmpty()) {
            persistOrRestore(previous);
        }

        return result;
    }

    @Override
    public Optional<E> delete(ID id) {
        Map<ID, E> previous = snapshot();
        Optional<E> result = super.delete(id);

        if (result.isPresent()) {
            persistOrRestore(previous);
        }

        return result;
    }


    /**
     * Persists a change, restoring the previous in-memory state if persistence fails.
     * @param previous state before the operation
     * @throws RepositoryException the original persistence failure, after restoring memory
     */
    private void persistOrRestore(Map<ID, E> previous) {
        try { writeToFile(); }
        catch (RepositoryException e) {
            restore(previous);
            throw e;
        }
    }
}
