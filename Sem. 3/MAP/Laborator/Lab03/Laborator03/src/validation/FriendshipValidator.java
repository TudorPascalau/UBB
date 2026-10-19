package validation;

import domain.Friendship;
import domain.User;
import repository.Repository;

/**
 * Validates friendship fields and the existence of both participants.
 */
public class FriendshipValidator implements Validator<Friendship> {
    private final Repository<Long, User> users;

    /**
     * Creates a friendship validator.
     * @param users repository used to resolve participant IDs
     * @throws IllegalArgumentException if the repository is null
     */
    public FriendshipValidator(Repository<Long, User> users) {
        if (users == null) throw new IllegalArgumentException("User repository cannot be null");
        this.users = users;
    }
    /**
     * Checks entity validity.
     * @param friendship friendship to validate
     * @throws ValidationException if fields or participant references are invalid
     */
    @Override public void validate(Friendship friendship) {
        if (friendship == null) throw new ValidationException("Friendship cannot be null");
        StringBuilder errors = new StringBuilder();
        Long first = friendship.getFirstUserId();
        Long second = friendship.getSecondUserId();
        if (first <= 0 || second <= 0) errors.append("User IDs must be positive. ");
        if (first.equals(second)) errors.append("Friendship cannot be with self. ");
        if (friendship.getFriendsSince() == null) errors.append("Friendship date is required. ");
        if (users.findOne(first) == null || users.findOne(second) == null)
            errors.append("Both users must exist. ");
        if (!errors.isEmpty()) throw new ValidationException(errors.toString().trim());
    }
}
