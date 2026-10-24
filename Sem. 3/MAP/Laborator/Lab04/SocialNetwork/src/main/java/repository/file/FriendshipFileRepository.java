package repository.file;
import domain.Friendship;
import domain.FriendshipId;
import repository.RepositoryException;
import validation.Validator;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

/**
 * Converts firstUserId;secondUserId;ISO-date text records.
 */
public final class FriendshipFileRepository extends AbstractFileRepository<FriendshipId, Friendship> {
    /**
     * Creates a friendship file repository.
     * @param fileName relative friendship data path
     * @param validator friendship validation strategy
     * @throws RepositoryException if input cannot be read or contains corrupt records
     */
    public FriendshipFileRepository(String fileName, Validator<Friendship> validator) {
        super(fileName, validator);
        loadData();
    }
    @Override protected Friendship extractEntity(String line) {
        String[] fields = line.split(";", -1);
        if (fields.length != 3)
            throw new IllegalArgumentException("Expected firstUserId;secondUserId;ISO-date");
        return new Friendship(Long.parseLong(fields[0].trim()), Long.parseLong(fields[1].trim()),
                LocalDateTime.parse(fields[2], DateTimeFormatter.ISO_LOCAL_DATE_TIME));
    }
    @Override protected String createEntityAsString(Friendship friendship) {
        return friendship.getFirstUserId() + ";" + friendship.getSecondUserId() + ";"
                + friendship.getFriendsSince().format(DateTimeFormatter.ISO_LOCAL_DATE_TIME);
    }
}
