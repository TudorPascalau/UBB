package domain;

import java.util.Objects;

public class FriendshipId {
    private final Long firstUserId;
    private final Long secondUserId;

    public FriendshipId(Long firstUserId, Long secondUserId) {
        Objects.requireNonNull(firstUserId, "firstUserId is null");
        Objects.requireNonNull(secondUserId, "secondUserId is null");

        if(firstUserId.compareTo(secondUserId) <= 0) {
            this.firstUserId = firstUserId;
            this.secondUserId = secondUserId;
        }
        else {
            this.firstUserId = secondUserId;
            this.secondUserId = firstUserId;
        }
    }

    public Long getFirstUserId() {
        return firstUserId;
    }

    public Long getSecondUserId() {
        return secondUserId;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        FriendshipId friendshipId = (FriendshipId) o;
        return firstUserId.equals(friendshipId.firstUserId) && secondUserId.equals(friendshipId.secondUserId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(firstUserId, secondUserId);
    }

    @Override
    public String toString() {
        return "(" + firstUserId + ", " + secondUserId + ")";
    }
}
