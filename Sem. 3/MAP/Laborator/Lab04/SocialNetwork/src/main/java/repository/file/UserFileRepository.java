package repository.file;
import domain.User;
import repository.RepositoryException;
import validation.Validator;

/**
 * Converts id;firstName;lastName text records.
 */
public final class UserFileRepository extends AbstractFileRepository<Long, User> {
    /**
     * Creates a user file repository.
     * @param fileName relative user data path
     * @param validator user validation strategy
     * @throws IllegalArgumentException if the path or validator is null, or the path is absolute
     * @throws java.nio.file.InvalidPathException if the path is invalid
     * @throws RepositoryException if input cannot be read or contains corrupt records
     */
    public UserFileRepository(String fileName, Validator<User> validator) {
        super(fileName, validator);
        loadData();
    }
    @Override protected User extractEntity(String line) {
        String[] fields = line.split(";", -1);
        if (fields.length != 3)
            throw new IllegalArgumentException("Expected id;firstName;lastName");
        return new User(Long.parseLong(fields[0].trim()), fields[1], fields[2]);
    }
    @Override protected String createEntityAsString(User user) {
        return user.getId() + ";" + user.getFirstName() + ";" + user.getLastName();
    }
}
