package domain;

import java.util.Objects;
import java.util.Set;

/**
 * Immutable connected component represented by user IDs.
 */
public final class Community {
    private final Set<Long> userIds;

    /**
     * Creates a community.
     * @param userIds component members
     * @throws NullPointerException if members are null
     * @throws IllegalArgumentException if members are empty
     */
    public Community(Set<Long> userIds) {
        Objects.requireNonNull(userIds, "Community members cannot be null");

        if(userIds.isEmpty()) {
            throw new IllegalArgumentException("A community must have at least one user");
        }

        this.userIds = Set.copyOf(userIds);
    }

    /**
     * Returns the member identifiers.
     * @return component members
     */
    public Set<Long> getUserIds() {
        return userIds;
    }

    /**
     * Returns the number of members.
     * @return number of members
     */
    public int  size() {
        return userIds.size();
    }

    /**
     * Compares object values.
     * @param o compared object
     * @return whether members match
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Community)) return false;

        Community community = (Community) o;
        return userIds.equals(community.userIds);
    }

    /**
     * Returns a hash consistent with equality.
     * @return a hash consistent with equality
     */
    @Override
    public int hashCode() {
        return userIds.hashCode();
    }

    /**
     * Returns a readable description.
     * @return component members as text
     */
    @Override
    public String toString() {
        return "Community: " + userIds;
    }
}
