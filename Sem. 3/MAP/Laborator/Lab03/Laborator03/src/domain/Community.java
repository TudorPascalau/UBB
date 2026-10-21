package domain;

import java.util.Objects;
import java.util.Set;

/**
 * An immutable group of users belonging to the same friendship community.
 */
public final class Community {
    private final Set<Long> userIds;

    /**
     * Creates a community.
     * @param userIds component members
     * @throws NullPointerException if the member set is null or contains null
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
     * @return an unmodifiable set of member identifiers
     */
    public Set<Long> getUserIds() {
        return userIds;
    }

    /**
     * Returns the number of members.
     * @return number of members
     */
    public int size() {
        return userIds.size();
    }

    /**
     * Compares communities by their members.
     * @param o compared object
     * @return whether members match
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Community community)) return false;

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
     * @return an unmodifiable set of member identifiers as text
     */
    @Override
    public String toString() {
        return "Community: " + userIds;
    }
}
