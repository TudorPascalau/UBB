package repository;

import domain.Friendship;
import domain.FriendshipId;
import validation.Validator;

public class FriendshipFileRepository
        extends AbstractFileRepository<FriendshipId, Friendship> {

    public FriendshipFileRepository(String fileName) {
        super(fileName);
        loadFromFile();
    }

    @Override
    protected Friendship fromCsv(String line) {
        String[] fields = line.split(",", -1);

        if (fields.length != 2) {
            throw new IllegalArgumentException("Format asteptat: firstUserId,secondUserId");
        }

        return new Friendship(Long.parseLong(fields[0].trim()), Long.parseLong(fields[1].trim()));
    }

    @Override
    protected String toCsv(Friendship friendship) {
        return friendship.getFirstUserId() + "," + friendship.getSecondUserId();
    }
}
