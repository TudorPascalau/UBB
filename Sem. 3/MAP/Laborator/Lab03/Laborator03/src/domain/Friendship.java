package domain;

public class Friendship extends Entity<FriendshipId> {

    public Friendship(Long id, String firstUsername, String secondUsername) {
        super(new FriendshipId(id, firstUsername, secondUsername));
    }

    public Long getNumericId() {
        return getId().getId();
    }

    public String getFirstUsername() {
        return getId().getFirstUsername();
    }

    public String getSecondUsername() {
        return getId().getSecondUsername();
    }

    @Override
    public String toString() {
        return "Friendship{id=" + getNumericId()
                + ", firstUsername=" + getFirstUsername()
                + ", secondUsername=" + getSecondUsername() + "}";
    }
}
