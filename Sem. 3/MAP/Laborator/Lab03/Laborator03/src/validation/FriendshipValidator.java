package validation;

import domain.Friendship;

/**
 * Validates friendship fields; the service checks participant existence.
 */
public class FriendshipValidator implements Validator<Friendship> {

    /**
     * Creates a friendship validator.
     */
    public FriendshipValidator() {}
    /**
     * Checks entity validity.
     * @param friendship friendship to validate
     * @throws ValidationException if friendship fields are invalid
     */
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
