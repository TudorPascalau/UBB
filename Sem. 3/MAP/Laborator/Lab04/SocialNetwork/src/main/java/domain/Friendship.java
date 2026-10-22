package domain;

import java.time.LocalDateTime;

/**
 * A friendship identified by its two participants, regardless of their order.
 */
public class Friendship extends Entity<FriendshipId> {
    private final LocalDateTime friendsSince;

    /**
     * Creates a friendship.
     * @param firstUserId first participant
     * @param secondUserId second participant
     * @param friendsSince date when the friendship started
     * @throws IllegalArgumentException if a participant ID is null
     */
    public Friendship(Long firstUserId, Long secondUserId, LocalDateTime friendsSince) {
        super(new FriendshipId(firstUserId, secondUserId));
        this.friendsSince = friendsSince;
    }
    /**
     * Returns the first participant ID.
     * @return the first user ID
     */
    public Long getFirstUserId() { return getId().getFirstUserId(); }
    /**
     * Returns the second participant ID.
     * @return the second user ID
     */
    public Long getSecondUserId() { return getId().getSecondUserId(); }
    /**
     * Returns the friendship date.
     * @return the friendship date
     */
    public LocalDateTime getFriendsSince() { return friendsSince; }
    /**
     * Returns a readable description.
     * @return a readable description
     */
    @Override public String toString() {
        return "Friendship: " + getId() + ", since " + friendsSince;
    }
}
