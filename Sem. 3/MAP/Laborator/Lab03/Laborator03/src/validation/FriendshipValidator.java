package validation;

import domain.Friendship;

public class FriendshipValidator implements Validator<Friendship> {

    @Override
    public void validate(Friendship friendship) {
        if(friendship == null) {
            throw new ValidationException("Friendship cannot be null");
        }

        if(friendship.getFirstUserId().equals(friendship.getSecondUserId())) {
            throw new ValidationException("Friendship cannot be with self");
        }
    }

}
