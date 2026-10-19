package repository;
import domain.User;
import validation.Validator;

/**
 * Converts id;firstName;lastName text records.
 */
public final class UserFileRepository extends AbstractFileRepository<Long, User> {
    /**
     * Creates a user file repository.
     * @param validator user validator
     * @throws RepositoryException if input cannot be read or contains corrupt records
     * @throws IllegalArgumentException if validator is null
     */
    public UserFileRepository(Validator<User> validator) {
        super(validator, "data/users.csv");
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
