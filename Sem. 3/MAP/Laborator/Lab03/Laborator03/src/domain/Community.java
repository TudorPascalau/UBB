package domain;

import java.util.Objects;
import java.util.Set;

public final class Community {
    private final Set<String> usernames;

    public Community(Set<String> usernames) {
        Objects.requireNonNull(usernames, "Community members cannot be null");

        if(usernames.isEmpty()) {
            throw new IllegalArgumentException("A community must have at least one user");
        }

        this.usernames = Set.copyOf(usernames);
    }

    public Set<String> getUsernames() {
        return usernames;
    }

    public int  size() {
        return usernames.size();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Community)) return false;

        Community community = (Community) o;
        return usernames.equals(community.usernames);
    }

    @Override
    public int hashCode() {
        return usernames.hashCode();
    }

    @Override
    public String toString() {
        return "Community: " + usernames;
    }
}
