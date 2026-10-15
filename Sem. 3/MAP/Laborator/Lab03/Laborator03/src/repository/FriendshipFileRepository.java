package repository;

import domain.Friendship;
import domain.FriendshipId;

public class FriendshipFileRepository
        extends AbstractFileRepository<FriendshipId, Friendship> {

    public FriendshipFileRepository(String fileName) {
        super(fileName);
        loadFromFile();
    }

    @Override
    protected Friendship fromCsv(String line) {
        String[] fields = line.split(",", -1);

        if (fields.length != 3) {
            throw new IllegalArgumentException("Format asteptat: id,firstUsername,secondUsername");
        }

        return new Friendship(Long.parseLong(fields[0].trim()), fields[1], fields[2]);
    }

    @Override
    protected String toCsv(Friendship friendship) {
        requireSimpleCsvField(friendship.getFirstUsername());
        requireSimpleCsvField(friendship.getSecondUsername());
        return friendship.getNumericId() + ","
                + friendship.getFirstUsername() + "," + friendship.getSecondUsername();
    }

    private void requireSimpleCsvField(String value) {
        if (value.contains(",") || value.contains("\"")
                || value.contains("\n") || value.contains("\r")) {
            throw new RepositoryException("Username cannot be represented in simplified CSV");
        }
    }
}
