package domain;

public class Friendship extends Entity<FriendshipId> {

    public Friendship(Long firstUserId, Long secondUserId) {
        super(new FriendshipId(firstUserId, secondUserId));
    }

    public Long getFirstUserId() {
        return getId().getFirstUserId();
    }

    public Long getSecondUserId() {
        return getId().getSecondUserId();
    }

    @Override
    public String toString() {
        return "Friendship{userIds=" + getId() + "}";
    }
}
