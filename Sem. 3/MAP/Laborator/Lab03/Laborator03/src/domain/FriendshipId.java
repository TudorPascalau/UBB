package domain;

import java.util.Objects;

public final class FriendshipId {
    private final Long id;
    private final String firstUsername;
    private final String secondUsername;

    public FriendshipId(Long id, String firstUsername, String secondUsername) {
        this.id = Objects.requireNonNull(id, "Friendship ID is null");
        Objects.requireNonNull(firstUsername, "firstUsername is null");
        Objects.requireNonNull(secondUsername, "secondUsername is null");

        if (firstUsername.compareTo(secondUsername) <= 0) {
            this.firstUsername = firstUsername;
            this.secondUsername = secondUsername;
        }
        else {
            this.firstUsername = secondUsername;
            this.secondUsername = firstUsername;
        }
    }

    public Long getId() {
        return id;
    }

    public String getFirstUsername() {
        return firstUsername;
    }

    public String getSecondUsername() {
        return secondUsername;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        FriendshipId friendshipId = (FriendshipId) o;
        return id.equals(friendshipId.id)
                && firstUsername.equals(friendshipId.firstUsername)
                && secondUsername.equals(friendshipId.secondUsername);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, firstUsername, secondUsername);
    }

    @Override
    public String toString() {
        return "(" + id + ", " + firstUsername + ", " + secondUsername + ")";
    }
}
