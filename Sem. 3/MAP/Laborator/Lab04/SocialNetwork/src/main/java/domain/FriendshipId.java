package domain;

import java.util.Objects;

/**
 * An immutable friendship identifier; reversing the participants gives an equal identifier.
 */
public final class FriendshipId {
    private final Long firstUserId;
    private final Long secondUserId;

    /**
     * Creates a friendship id.
     * @param firstUserId one participant
     * @param secondUserId the other participant
     * @throws IllegalArgumentException if either ID is null
     */
    public FriendshipId(Long firstUserId, Long secondUserId) {
        if (firstUserId == null || secondUserId == null)
            throw new IllegalArgumentException("User IDs cannot be null");
        this.firstUserId = Math.min(firstUserId, secondUserId);
        this.secondUserId = Math.max(firstUserId, secondUserId);
    }
    /**
     * Returns the first participant ID.
     * @return the smaller user ID
     */
    public Long getFirstUserId() { return firstUserId; }
    /**
     * Returns the second participant ID.
     * @return the larger user ID
     */
    public Long getSecondUserId() { return secondUserId; }
    /**
     * Compares friendship identifiers independently of participant order.
     * @param other object to compare
     * @return whether both IDs match
     */
    @Override public boolean equals(Object other) {
        if (this == other) return true;
        if (!(other instanceof FriendshipId pair)) return false;
        return firstUserId.equals(pair.firstUserId) && secondUserId.equals(pair.secondUserId);
    }
    /**
     * Returns a hash consistent with equality.
     * @return a hash consistent with equality
     */
    @Override public int hashCode() { return Objects.hash(firstUserId, secondUserId); }
    /**
     * Returns a readable description.
     * @return the normalized pair
     */
    @Override public String toString() { return "(" + firstUserId + ", " + secondUserId + ")"; }
}
