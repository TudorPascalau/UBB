package validation;

import domain.Friendship;

/**
 * Requires distinct positive participant IDs and a friendship date.
 */
public class FriendshipValidator implements Validator<Friendship> {

    /**
     * Creates a friendship validator.
     */
    public FriendshipValidator() {}
    @Override public void validate(Friendship friendship) {
        if (friendship == null) throw new ValidationException("Friendship cannot be null");
        StringBuilder errors = new StringBuilder();
        Long first = friendship.getFirstUserId();
        Long second = friendship.getSecondUserId();
        if (first <= 0 || second <= 0) errors.append("User IDs must be positive. ");
        if (first.equals(second)) errors.append("Friendship cannot be with self. ");
        if (friendship.getFriendsSince() == null) errors.append("Friendship date is required. ");

        if (!errors.isEmpty()) throw new ValidationException(errors.toString().trim());
    }
}
