package curs.repository.file;

import curs.domain.Entity;
import curs.domain.validators.Validator;
import curs.repository.InMemoryRepository;

import java.io.IOException;
import java.io.UncheckedIOException;
import java.nio.file.Files;
import java.nio.file.NoSuchFileException;
import java.nio.file.Path;
import java.util.List;
import java.util.Optional;
import java.util.function.Function;
import java.util.stream.Stream;

/**
 * Repository that keeps the entities in memory and in a text file (one entity per line).
 * Curs 3 used Template Method (AbstractFileRepository with two abstract methods,
 * one subclass per entity). Curs 5 uses composition: the conversion from / to a line
 * of text is received through the constructor as two functions, so the class is
 * no longer abstract. Reading and writing use java.nio.file.Files and streams.
 *
 * @param <ID> - type E must have an attribute of type ID
 * @param <E>  - type of entities saved in repository
 */
public class FileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {

    private final Path path;
    private final Function<String, E> parser;
    private final Function<E, String> formatter;

    /**
     * creates the repository and loads the entities from the file
     *
     * @param validator - the validation strategy for the entities
     * @param fileName  - the path of the text file
     * @param parser    - creates an entity from a line of the file
     * @param formatter - converts an entity into a line of the file
     */
    public FileRepository(Validator<E> validator, String fileName,
                          Function<String, E> parser, Function<E, String> formatter) {
        super(validator);
        this.path = Path.of(fileName);
        this.parser = parser;
        this.formatter = formatter;
        loadData();
    }

    /**
     * reads all the lines of the file and saves the entities in memory;
     * if the file does not exist, the repository starts empty
     *
     * @throws UncheckedIOException if the file cannot be read
     */
    private void loadData() {
        // Files.lines citeste lenes (lazy), linie cu linie; stream-ul tine fisierul
        // deschis, deci trebuie inchis: try-with-resources (Stream este AutoCloseable)
        try (Stream<String> lines = Files.lines(path)) {
            lines.filter(line -> !line.isBlank())
                    .map(parser)
                    .forEach(super::save);   // super, nu this: nu rescriem fisierul in timp ce il citim
        } catch (NoSuchFileException e) {
            System.out.println("Fisierul " + path + " nu exista; repository gol.");
        } catch (IOException e) {
            throw new UncheckedIOException("Eroare la citirea fisierului " + path, e);
        }
    }

    /**
     * rewrites the whole file with the entities currently in memory
     *
     * @throws UncheckedIOException if the file cannot be written
     */
    private void writeToFile() {
        List<String> lines = stream().map(formatter).toList();
        try {
            Files.write(path, lines);
        } catch (IOException e) {
            throw new UncheckedIOException("Eroare la scrierea fisierului " + path, e);
        }
    }

    /**
     * saves the entity in memory and, if it was saved, rewrites the file
     *
     * @param entity entity must be not null
     * @return Optional.empty() - if the given entity is saved
     * otherwise returns an Optional with the entity (id already exists)
     * @throws curs.domain.validators.ValidationException if the entity is not valid
     * @throws IllegalArgumentException                   if the given entity is null.
     */
    @Override
    public Optional<E> save(E entity) {
        Optional<E> result = super.save(entity);
        if (result.isEmpty())
            writeToFile();
        return result;
    }

    /**
     * removes the entity from memory and, if it existed, rewrites the file
     *
     * @param id id must be not null
     * @return an Optional with the removed entity
     * or Optional.empty() - if there is no entity with the given id
     */
    @Override
    public Optional<E> delete(ID id) {
        Optional<E> result = super.delete(id);
        result.ifPresent(e -> writeToFile());
        return result;
    }

    /**
     * updates the entity in memory and, if it was updated, rewrites the file
     *
     * @param entity entity must not be null
     * @return Optional.empty() - if the entity is updated,
     * otherwise returns an Optional with the entity - (e.g id does not exist).
     * @throws IllegalArgumentException                   if the given entity is null.
     * @throws curs.domain.validators.ValidationException if the entity is not valid.
     */
    @Override
    public Optional<E> update(E entity) {
        Optional<E> result = super.update(entity);
        if (result.isEmpty())
            writeToFile();
        return result;
    }
}
