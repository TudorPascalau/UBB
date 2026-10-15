package validation;

import domain.Friendship;

public class FriendshipValidator implements Validator<Friendship> {

    @Override
    public void validate(Friendship friendship) {
        if(friendship == null) {
            throw new ValidationException("Friendship cannot be null");
        }

        if (friendship.getNumericId() <= 0) {
            throw new ValidationException("Friendship ID must be positive");
        }

        if (friendship.getFirstUsername().isBlank() || friendship.getSecondUsername().isBlank()) {
            throw new ValidationException("Usernames cannot be empty");
        }

        if (friendship.getFirstUsername().equalsIgnoreCase(friendship.getSecondUsername())) {
            throw new ValidationException("Friendship cannot be with self");
        }
    }

}
